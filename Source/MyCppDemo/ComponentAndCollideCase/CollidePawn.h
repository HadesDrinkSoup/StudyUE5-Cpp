// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawnMovementComponent.h"
#include "CollidePawn.generated.h"

/**
 * ACollidePawn类实现了一个带有自定义移动组件的碰撞pawn
 * 包含球形网格、弹簧臂、摄像机视角和Niagara特效系统
 */
UCLASS()
class MYCPPDEMO_API ACollidePawn : public APawn
{
    GENERATED_BODY()

public:
    // 构造函数，设置默认属性值
    ACollidePawn();

    // 球形静态网格组件，作为pawn的视觉表示和碰撞体
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UStaticMeshComponent* SphereComp;

    // 摄像机组件，用于 pawn 的视角
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UCameraComponent* CameraComp;

    // 弹簧臂组件，实现摄像机平滑跟随效果
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USpringArmComponent* SpringArmComp;

    // Niagara特效组件，用于视觉特效（如尾迹、粒子效果等）
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UNiagaraComponent* NiagaraComp;

    // 自定义移动组件，处理pawn的移动逻辑
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UMyPawnMovementComponent* MyMovementComponent;

protected:
    // 游戏开始或pawn生成时调用
    virtual void BeginPlay() override;

public:
    // 每帧调用，处理帧更新逻辑
    virtual void Tick(float DeltaTime) override;

    // 设置玩家输入绑定
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};