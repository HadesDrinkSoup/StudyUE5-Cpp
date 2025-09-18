// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerCase/TimerActor.h"
#include "Components/TextRenderComponent.h"

// 设置默认值
ATimerActor::ATimerActor()
{
	// 设置此Actor每帧调用Tick()。如果您不需要它，可以关闭以提高性能。
	PrimaryActorTick.bCanEverTick = false;

	// 创建文本渲染组件
	TextRenderComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComp"));
	// 设置文本水平对齐方式为居中
	TextRenderComp->SetHorizontalAlignment(EHTA_Center);
	// 设置文本大小
	TextRenderComp->SetWorldSize(150.0f);
	// 设置初始文本
	TextRenderComp->SetText(FText::FromString(TEXT("Count Down!")));
	// 设置文本组件为根组件
	RootComponent = TextRenderComp;
	// 初始化倒计时时间
	CountDown = 3;
}

// 游戏开始或生成时调用
void ATimerActor::BeginPlay()
{
	Super::BeginPlay();
	// 立即更新一次显示
	UpdateTimerDisplay();
	// 设置定时器，每秒执行一次AddvanceTimer
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATimerActor::AddvanceTimer, 1.0f, true);
}

// 每帧调用
void ATimerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 定时器回调函数
void ATimerActor::AddvanceTimer()
{
	// 减少倒计时
	CountDown--;

	// 更新显示
	UpdateTimerDisplay();

	if (CountDown == 0)
	{
		// 倒计时结束，调用完成事件
		TimerFinished();
	}
	else if (CountDown < 0)
	{
		// 倒计时已完成，清除定时器并销毁Actor
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Destroy();
	}
}

// 定时器完成事件的实现
void ATimerActor::TimerFinished_Implementation()
{
	// 设置完成文本
	TextRenderComp->SetText(FText::FromString(TEXT("Go!")));
}

// 更新计时器显示
void ATimerActor::UpdateTimerDisplay()
{
	// 显示剩余时间
	TextRenderComp->SetText(FText::AsNumber(CountDown));
}