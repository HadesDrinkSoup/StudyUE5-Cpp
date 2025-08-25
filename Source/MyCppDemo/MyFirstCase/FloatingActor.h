// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h" // 必须包含的生成头文件

/**
 * 浮动Actor类
 * 这是一个会在场景中上下浮动并旋转的Actor示例
 */
UCLASS() // UE的类声明宏
class MYCPPDEMO_API AFloatingActor : public AActor // 继承自AActor
{
	GENERATED_BODY() // UE代码生成宏，必须包含在UCLASS类中

public:
	// 设置此Actor属性的默认值
	AFloatingActor();

	// 静态网格体组件指针，用于视觉表现
	UStaticMeshComponent* VisualMesh;

	// 浮动速度参数，可在编辑器和蓝图中调整
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingActor")
	float FloatSpeed = 20.0f;

	// 旋转速度参数，可在编辑器和蓝图中调整
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingActor")
	float RotationSpeed = 20.0f;

protected:
	// 当游戏开始或生成时调用
	virtual void BeginPlay() override;

public:
	// 每帧调用
	virtual void Tick(float DeltaTime) override;

};