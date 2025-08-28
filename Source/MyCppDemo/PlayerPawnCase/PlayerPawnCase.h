
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputLibrary.h"
#include "PlayerPawnCase.generated.h"

// 自定义玩家Pawn类，继承自APawn
UCLASS()
class MYCPPDEMO_API APlayerPawnCase : public APawn
{
    GENERATED_BODY()

public:
    // 构造函数
    APlayerPawnCase();

    // 静态网格组件，用于视觉表示
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UStaticMeshComponent* StaticMeshComp;

    // 摄像机组件，用于玩家视角
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UCameraComponent* CameraComp;

    // 弹簧臂组件，用于平滑摄像机移动
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USpringArmComponent* SpringArmComp;

    // 浮动Pawn移动组件，处理移动逻辑
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UFloatingPawnMovement* MovementComp;

    // 缩放灵敏度，控制缩放速度
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float ZoomSensitivity = 20.0f;

    // 最小缩放距离，限制弹簧臂长度
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float MinZoomLength = 200.0f;

    // 最大缩放距离，限制弹簧臂长度
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float MaxZoomLength = 800.0f;

protected:
    // 游戏开始或生成时调用
    virtual void BeginPlay() override;

    // 输入动作：移动
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* MoveAction;

    // 输入动作：观察（旋转视角）
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* LookAction;

    // 输入动作：镜头缩放
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputAction* ZoomAction;

    // 默认输入映射上下文
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputMappingContext* DefaultMappingContext;

    // 处理移动输入
    void Move(const FInputActionValue& Value);

    // 处理观察（旋转）输入
    void Look(const FInputActionValue& Value);

    // 处理缩放输入
    void Zoom(const FInputActionValue& Value);

public:
    // 每帧调用
    virtual void Tick(float DeltaTime) override;

    // 设置玩家输入组件
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};