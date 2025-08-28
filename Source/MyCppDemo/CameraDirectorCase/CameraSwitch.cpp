// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirectorCase/CameraSwitch.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

// 设置默认值
ACameraSwitch::ACameraSwitch()
{
    // 设置此Actor每帧调用Tick()，不需要时可关闭以提高性能
    PrimaryActorTick.bCanEverTick = true;
}

// 游戏开始或生成时调用
void ACameraSwitch::BeginPlay()
{
    Super::BeginPlay();

    // 获取玩家控制器引用
    OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

    // 如果相机列表为空，自动查找所有相机
    if (CameraList.Num() == 0)
    {
        FindAllCameras();
    }

    // 设置初始视图目标
    if (OurPlayerController && CameraList.Num() > 0)
    {
        // 将视图目标设置为列表中的第一个相机
        OurPlayerController->SetViewTarget(CameraList[0].Camera);
        // 初始化计时器为第一个相机的切换间隔时间
        TimeToNextCameraChange = CameraList[0].TimeBetweenCameraChanges;
    }
}

// 每帧调用
void ACameraSwitch::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 确保有相机可切换
    if (CameraList.Num() <= 0 || !OurPlayerController)
        return;

    // 更新相机切换计时器
    TimeToNextCameraChange -= DeltaTime;

    // 检查是否到达切换时间
    if (TimeToNextCameraChange <= 0.0f)
    {
        // 获取下一个相机索引（循环递增）
        CurrentCameraIndex = (CurrentCameraIndex + 1) % CameraList.Num();
        // 输出日志，记录当前切换的相机索引
        UE_LOG(LogTemp, Log, TEXT("Switching to camera index: %d"), CurrentCameraIndex);
        // 获取当前相机信息
        FCameraSwitchInfo& CameraInfo = CameraList[CurrentCameraIndex];

        // 重置计时器为当前相机的切换间隔时间
        TimeToNextCameraChange = CameraInfo.TimeBetweenCameraChanges;

        // 切换到下一个相机
        if (CameraInfo.Camera)
        {
            // 使用平滑过渡效果切换相机视图
            OurPlayerController->SetViewTargetWithBlend(CameraInfo.Camera, CameraInfo.SmoothBlendTime);
        }
    }
}

// 查找场景中所有相机
void ACameraSwitch::FindAllCameras()
{
    // 清空现有的相机列表
    CameraList.Empty();
    // 获取场景中所有的摄像机Actor
    TArray<AActor*> FoundCameras;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);
    // 遍历找到的摄像机Actor并添加到相机列表中
    for (AActor* CameraActor : FoundCameras)
    {
        if (CameraActor)
        {
            // 创建新的相机信息结构体
            FCameraSwitchInfo NewCameraInfo;
            // 设置相机引用（需要强制类型转换为ACameraActor*）
            NewCameraInfo.Camera = Cast<ACameraActor>(CameraActor);
            // 将相机信息添加到列表中
            CameraList.Add(NewCameraInfo);
        }
    }
}