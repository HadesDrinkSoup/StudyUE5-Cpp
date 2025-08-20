// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBaseActor.h"

// Sets default values
AMyBaseActor::AMyBaseActor()
	:Health(200)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//根组件设置为默认子对象才在世界场景中有变换
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComponet"));

	Health = 300;
}

int32 AMyBaseActor::GetCurrentHealth()
{
	return Health;
}

int32 AMyBaseActor::GetCDOHealth()
{
	//获得类默认对象
	AMyBaseActor * CDOHealth = AMyBaseActor::StaticClass()->GetDefaultObject<AMyBaseActor>();
	if (CDOHealth) {
		return CDOHealth->Health;
	}
	return -1;
}

// Called when the game starts or when spawned
void AMyBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

