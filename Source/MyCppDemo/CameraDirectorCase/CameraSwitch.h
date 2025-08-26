// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraSwitch.generated.h"

/**
 * ACameraSwitch类
 * 用于在两个相机之间切换的Actor
 * 支持定时切换和平滑过渡效果
 */
UCLASS()
class MYCPPDEMO_API ACameraSwitch : public AActor
{
	GENERATED_BODY()

public:
	// 构造函数，设置默认值
	ACameraSwitch();

	// 相机一的引用，可在编辑器任意位置编辑
	UPROPERTY(EditAnywhere)
	AActor* CameraOne;

	// 相机二的引用，可在编辑器任意位置编辑
	UPROPERTY(EditAnywhere)
	AActor* CameraTwo;

	// 下一次相机切换的倒计时
	float TimeToNextCameraChange;

	// 相机切换的时间间隔（秒），可在蓝图读写，归类为ChangeCamera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeCamera")
	float TimeBetweenCameraChanges = 2.0f;

	// 相机平滑过渡的时间（秒），可在蓝图读写，归类为ChangeCamera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeCamera")
	float SmoothBlendTime = 0.75f;

	// 玩家控制器引用，用于控制相机视图切换
	APlayerController* OurPlayerController;


protected:
	// 游戏开始或生成时调用
	virtual void BeginPlay() override;

public:
	// 每帧调用
	virtual void Tick(float DeltaTime) override;
};