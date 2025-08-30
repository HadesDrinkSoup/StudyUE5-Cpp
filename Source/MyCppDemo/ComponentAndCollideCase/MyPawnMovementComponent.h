// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputLibrary.h"
#include "MyPawnMovementComponent.generated.h"

/**
 * UMyPawnMovementComponent类
 * 自定义pawn移动组件，使用增强输入系统处理玩家输入和移动逻辑
 */
UCLASS()
class MYCPPDEMO_API UMyPawnMovementComponent : public UPawnMovementComponent
{
    GENERATED_BODY()

public:
    // 每帧组件更新函数，处理移动逻辑
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // 设置输入绑定
    void SetupInput(UEnhancedInputComponent* EnhancedInputComponent);

    // 默认输入映射上下文
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputMappingContext* DefaultMappingContext;

    // 移动输入动作
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* MoveAction;

    // 视角旋转输入动作
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* LookAction;

    // 切换Niagara特效输入动作
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* ToggleNiagaraAction;

    // 移动速度参数
    UPROPERTY(EditAnywhere, Category = "Speed")
    float Speed = 300.0f;

    // 移动处理函数
    void Move(const FInputActionValue& Value);

    // 视角旋转处理函数
    void Look(const FInputActionValue& Value);
};