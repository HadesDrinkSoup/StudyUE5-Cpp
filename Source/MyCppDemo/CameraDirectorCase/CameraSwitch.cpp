// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirectorCase/CameraSwitch.h"
#include "Kismet/GameplayStatics.h"

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

	// 设置初始视图目标为CameraOne
	if (OurPlayerController && CameraOne)
	{
		OurPlayerController->SetViewTarget(CameraOne);
	}
}

// 每帧调用
void ACameraSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 更新相机切换计时器
	TimeToNextCameraChange -= DeltaTime;

	// 检查是否到达切换时间
	if (TimeToNextCameraChange <= 0.0f)
	{
		// 重置计时器
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		// 确保我们有玩家控制器
		if (!OurPlayerController)
		{
			OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		}

		if (OurPlayerController)
		{
			// 如果当前视图目标不是CameraOne且CameraOne有效，则切换到CameraOne
			if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			{
				// 使用平滑过渡效果切换到CameraOne
				OurPlayerController->SetViewTargetWithBlend(CameraOne, SmoothBlendTime);
			}
			// 如果当前视图目标不是CameraTwo且CameraTwo有效，则切换到CameraTwo
			else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
			{
				// 使用平滑过渡效果切换到CameraTwo
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
		}
	}
}