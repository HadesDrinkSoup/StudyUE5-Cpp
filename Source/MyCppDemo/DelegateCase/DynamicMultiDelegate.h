// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.h"
#include "DynamicMultiDelegate.generated.h"

UCLASS()
class MYCPPDEMO_API ADynamicMultiDelegate : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADynamicMultiDelegate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 统一修改所有Actor的分数（蓝图调用）
	UFUNCTION(BlueprintCallable, Category = "Delegate")
	void ChangeAllScores(int32 ScoreToAdd);


	// 获取管理的Actor数量
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Delegate")
	int32 GetManagedActorCount() const { return MyActorRefs.Num(); }

	// 查找并添加所有MyActor到引用数组（蓝图调用）
	UFUNCTION(BlueprintCallable, Category = "Delegate")
	void FindAllMyActors();

	// 清空引用数组（蓝图调用）
	UFUNCTION(BlueprintCallable, Category = "Delegate")
	void ClearAllActorRefs();

public:
	// 存储所有MyActor引用（蓝图可读写）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Delegate")
	TArray<AMyActor*> MyActorRefs;
};