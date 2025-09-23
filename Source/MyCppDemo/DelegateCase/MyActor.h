#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

// 委托声明

// 无参数的普通委托
DECLARE_DELEGATE(FScoreDelegate);

// 带一个int32参数的普通委托
DECLARE_DELEGATE_OneParam(FScoreDelegate_OneParam, int32);

// 无参数的多播委托（支持多个绑定）
DECLARE_MULTICAST_DELEGATE(FScoreMulticastDelegate);

UCLASS()
class MYCPPDEMO_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	// 构造函数
	AMyActor();

protected:
	// 游戏开始时调用
	virtual void BeginPlay() override;

public:
	// 每帧调用
	virtual void Tick(float DeltaTime) override;

public:
	// 委托实例

	// 分数变化单播委托（只能绑定一个函数）
	FScoreDelegate ScoreChangeDelegate;

	// 带参数的分数变化单播委托
	FScoreDelegate_OneParam ScoreChangeDelegate_OneParam;

	// 分数变化多播委托（可以绑定多个函数）
	FScoreMulticastDelegate ScoreChangeMulticastDelegate;

	// 设置分数并触发委托
	UFUNCTION(BlueprintCallable)
	void SetScore(int32 NewScore);

	// 仅打印当前分数，不触发委托
	void PrintScore();

	// 获取当前分数
	// @return 当前分数值
	int32 GetScore() const { return Score; }

private:
	// 玩家唯一标识
	FGuid PlayerId;

	// 当前分数
	int32 Score;
};