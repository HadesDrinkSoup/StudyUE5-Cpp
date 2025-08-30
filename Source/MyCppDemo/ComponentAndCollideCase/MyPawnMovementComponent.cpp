// Fill out your copyright notice in the Description page of Project Settings.

#include "ComponentAndCollideCase/MyPawnMovementComponent.h"
#include "InputActionValue.h" // 输入映射Value值的头文件
#include "EnhancedInputComponent.h" // 增强输入组件的头文件
#include "EnhancedInputSubsystems.h" // 增强输入子系统的头文件

// 每帧组件更新函数，处理移动逻辑
void UMyPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction); // 调用父类实现

    // 确保我们有要更新的组件、Pawn所有者且不应跳过更新
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    // 消费输入向量并应用移动，限制最大速度为1.0f
    FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * Speed;

    // 如果期望移动不为零，则执行移动
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        // 安全移动更新组件，考虑碰撞
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        // 如果发生碰撞，尝试沿表面滑动
        if (Hit.IsValidBlockingHit())
        {
            SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
        }
    }
}

// 设置输入绑定
void UMyPawnMovementComponent::SetupInput(UEnhancedInputComponent* PlayerInputComponent)
{
    // 确保输入组件有效
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // 绑定移动和视角输入动作
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UMyPawnMovementComponent::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UMyPawnMovementComponent::Look);
    }
}

// 处理视角旋转输入
void UMyPawnMovementComponent::Look(const FInputActionValue& Value)
{
    // 获取输入的2D向量值
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    // 如果存在玩家控制器，添加俯仰和偏航输入
    if (APlayerController* PlayerController = Cast<APlayerController>(GetOwner()->GetInstigatorController()))
    {
        PlayerController->AddPitchInput(LookAxisVector.Y);
        PlayerController->AddYawInput(LookAxisVector.X);
    }

    // 如果Pawn所有者存在，设置其旋转
    if (PawnOwner != nullptr)
    {
        FRotator ControlRotation = PawnOwner->GetControlRotation();
        // 限制俯仰角度在-60到60度之间
        float newPitch = FMath::Clamp(ControlRotation.Pitch + LookAxisVector.Y, -60.0f, 60.0f);
        float newYaw = ControlRotation.Yaw + LookAxisVector.X;
        // 设置Pawn的旋转
        PawnOwner->SetActorRotation(FRotator(newPitch, newYaw, 0.0f));
    }
}

// 处理移动输入
void UMyPawnMovementComponent::Move(const FInputActionValue& Value)
{
    // 获取输入的2D移动向量
    FVector2D MoveAxisVector = Value.Get<FVector2D>();

    // 如果Pawn所有者存在，处理移动
    if (PawnOwner != nullptr)
    {
        // 创建仅包含Yaw的旋转
        FRotator YawRotation(0.0f, PawnOwner->GetControlRotation().Yaw, 0.0f);

        // 获取前进和右方向向量
        FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // 添加移动输入
        PawnOwner->AddMovementInput(ForwardDirection, MoveAxisVector.Y);
        PawnOwner->AddMovementInput(RightDirection, MoveAxisVector.X);
    }
}