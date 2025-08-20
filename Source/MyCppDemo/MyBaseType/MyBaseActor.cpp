// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBaseActor.h"

// Sets default values
AMyBaseActor::AMyBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

