// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingActorCase/FloatingActor.h"

// 构造函数：在对象创建时调用
AFloatingActor::AFloatingActor()
{
    // 设置此Actor每帧调用Tick()，如果不需要可以提高性能关闭此特性
    PrimaryActorTick.bCanEverTick = true;
    
    // 创建静态网格组件并命名为"VisualMesh"
    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    // 将网格组件附加到根组件（RootComponent）
    VisualMesh->SetupAttachment(RootComponent);
}

// BeginPlay：当游戏开始或Actor被生成时调用
void AFloatingActor::BeginPlay()
{
    Super::BeginPlay(); // 调用父类的BeginPlay方法
}

// Tick：每一帧都会被调用
// 参数DeltaTime：自上一帧过去的时间（以秒为单位）
void AFloatingActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime); // 调用父类的Tick方法

    // 获取Actor的当前位置和旋转
    FVector NewLocation = GetActorLocation();
    FRotator NewRotation = GetActorRotation();

    // 获取游戏开始后的总运行时间
    const float RunningTime = GetGameTimeSinceCreation();

    // 计算高度变化量：使用正弦函数模拟上下浮动效果
    // FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime) 计算正弦函数的增量
    float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

    // 应用浮动速度和高度变化量到Z轴坐标
    NewLocation.Z += DeltaHeight * FloatSpeed;

    // 计算旋转变化量：根据旋转速度和帧时间计算
    float DeltaRotation = DeltaTime * RotationSpeed;

    // 将旋转变化量应用到Yaw（偏航角）
    NewRotation.Yaw += DeltaRotation;

    // 更新Actor的位置和旋转
    SetActorLocationAndRotation(NewLocation, NewRotation);
}