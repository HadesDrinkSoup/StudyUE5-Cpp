// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerActor.generated.h"

// 定时器Actor类，用于实现倒计时功能
UCLASS()
class MYCPPDEMO_API ATimerActor : public AActor
{
	GENERATED_BODY()

public:
	// 构造函数，设置默认属性
	ATimerActor();

	// 文本渲染组件，用于显示倒计时
	class UTextRenderComponent* TextRenderComp;

protected:
	// 定时器句柄，用于管理定时器
	FTimerHandle TimerHandle;

	// 倒计时时间（秒），可在编辑器中调整
	UPROPERTY(EditAnywhere, Category = "Timer")
	int32 CountDown;

protected:
	// 游戏开始或生成时调用
	virtual void BeginPlay() override;

	// 定时器回调函数，每秒执行一次
	void AddvanceTimer();

	// 定时器结束时的回调事件（BlueprintNativeEvent表示可在蓝图中重写）
	UFUNCTION(BlueprintNativeEvent)
	void TimerFinished();

	// 更新文本显示
	void UpdateTimerDisplay();

public:
	// 每帧调用
	virtual void Tick(float DeltaTime) override;
};