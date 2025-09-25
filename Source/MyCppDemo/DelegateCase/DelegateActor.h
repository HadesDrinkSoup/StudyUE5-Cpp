#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.h"
#include "DelegateActor.generated.h"

UCLASS()
class MYCPPDEMO_API ADelegateActor : public AActor
{
	GENERATED_BODY()

public:
	// 构造函数
	ADelegateActor();

protected:
	// 游戏开始时调用
	virtual void BeginPlay() override;

public:
	// 每帧调用
	virtual void Tick(float DeltaTime) override;

	// 委托回调函数 - 无参数版本
	void OnScoreChange();

	// 委托回调函数 - 带参数版本
	// @param Score - 传递的分数值
	void OnScoreChange(int32 Score, int32 Health);

private:
	// 指向MyActor的引用（用于绑定委托和调用方法）
	// 注意：这里没有使用UPROPERTY()，需要确保MyActorRef的生命周期管理
	AMyActor* MyActorRef;
};