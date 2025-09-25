// Fill out your copyright notice in the Description page of Project Settings.

#include "DelegateCase/DynamicMultiDelegate.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADynamicMultiDelegate::ADynamicMultiDelegate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADynamicMultiDelegate::BeginPlay()
{
	Super::BeginPlay();

	// 创建根组件
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}

	// 不再自动绑定委托，完全由蓝图控制
	// 如果需要查找所有MyActor，可以在蓝图中调用FindAllMyActors()
}

// Called every frame
void ADynamicMultiDelegate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 查找并添加所有MyActor到引用数组
void ADynamicMultiDelegate::FindAllMyActors()
{
	// 清空现有引用
	MyActorRefs.Empty();

	// 获取世界中所有的MyActor实例
	TArray<AActor*> MyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyActor::StaticClass(), MyActors);

	for (auto MyActor : MyActors)
	{
		if (MyActor)
		{
			AMyActor* Actor = Cast<AMyActor>(MyActor);
			if (Actor)
			{
				// 保存引用
				MyActorRefs.Add(Actor);
			}
		}
	}

}

// 清空引用数组
void ADynamicMultiDelegate::ClearAllActorRefs()
{
	MyActorRefs.Empty();
}

// 统一修改所有Actor的分数（可能导致递归）
void ADynamicMultiDelegate::ChangeAllScores(int32 ScoreToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("ChangeAllScores called - this may cause recursion if actors are bound to each other!"));

	for (auto Actor : MyActorRefs)
	{
		if (Actor && Actor->IsValidLowLevel())
		{
			int32 NewScore = Actor->GetScore() + ScoreToAdd;
			Actor->SetScore(NewScore);
		}
	}
}