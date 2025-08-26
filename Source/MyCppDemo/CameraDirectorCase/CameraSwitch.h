// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraSwitch.generated.h"

USTRUCT(BlueprintType)
struct FCameraSwitchInfo
{
	GENERATED_BODY()
public:

	// 相机的引用，可在编辑器任意位置编辑
	UPROPERTY(EditAnywhere)
	AActor* Camera = nullptr;

	// 相机切换的时间间隔（秒），可在蓝图读写，归类为ChangeCamera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeCamera")
	float TimeBetweenCameraChanges = 2.0f;

	// 相机平滑过渡的时间（秒），可在蓝图读写，归类为ChangeCamera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeCamera")
	float SmoothBlendTime = 0.75f;

};

UCLASS()
class MYCPPDEMO_API ACameraSwitch : public AActor
{
	GENERATED_BODY()

public:
	// 构造函数，设置默认值
	ACameraSwitch();

	// 下一次相机切换的倒计时
	float TimeToNextCameraChange;

	// 玩家控制器引用，用于控制相机视图切换
	APlayerController* OurPlayerController;

	// 当前相机索引
	int32 CurrentCameraIndex = 0;

protected:
	// 游戏开始或生成时调用
	virtual void BeginPlay() override;

public:
	// 每帧调用
	virtual void Tick(float DeltaTime) override;

	// 查找所有摄像机
	void FindAllCameras();

private:

	// 相机列表，包含多个相机及其切换参数
	UPROPERTY(VisibleAnywhere, Category = "CameraList")
	TArray<FCameraSwitchInfo> CameraList;

};