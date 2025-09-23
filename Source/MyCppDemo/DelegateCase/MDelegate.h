#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.h"  // 包含MyActor类的头文件
#include "MDelegate.generated.h"

UCLASS()
class MYCPPDEMO_API AMDelegate : public AActor
{
	GENERATED_BODY()

public:
	// 构造函数
	AMDelegate();

protected:
	// 游戏开始时调用
	virtual void BeginPlay() override;

	// 游戏结束或Actor被销毁时调用
	// @param EndPlayReason - 结束游戏的原因
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// 每帧调用
	virtual void Tick(float DeltaTime) override;

	// 外部调用来修改分数（可在蓝图中调用）
	UFUNCTION(BlueprintCallable)
	void ChangeScore();

private:
	// MyActor引用数组（UPROPERTY确保被垃圾回收系统管理）
	UPROPERTY()
	TArray<AMyActor*> MyActorRefs;

	// 委托回调函数 - 当分数改变时被调用
	void OnScoreChange();
};