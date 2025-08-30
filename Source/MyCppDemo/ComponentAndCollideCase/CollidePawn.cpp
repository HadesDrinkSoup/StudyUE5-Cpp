// Fill out your copyright notice in the Description page of Project Settings.

#include "ComponentAndCollideCase/CollidePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraComponent.h"

// 构造函数，设置默认值
ACollidePawn::ACollidePawn()
{
	// 设置此pawn每帧调用Tick()。如果不需要，可以关闭以提高性能
	PrimaryActorTick.bCanEverTick = true;

	// 创建球体碰撞组件作为根组件
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f); // 设置球体半径
	SphereComponent->SetCollisionProfileName(TEXT("Pawn")); // 设置碰撞配置文件

	// 创建静态网格组件，表示pawn的视觉外观
	SphereComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent); // 附加到根组件
	SphereComp->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f)); // 设置相对位置
	SphereComp->SetWorldScale3D(FVector(0.8f)); // 设置缩放

	// 创建弹簧臂组件，实现摄像机平滑跟随
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent); // 附加到根组件
	SpringArmComp->TargetArmLength = 400.0f; // 设置弹簧臂长度
	SpringArmComp->bEnableCameraLag = true; // 启用摄像机延迟
	SpringArmComp->CameraLagSpeed = 3.0f; // 设置摄像机延迟速度
	SpringArmComp->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); // 设置弹簧臂旋转角度

	// 创建摄像机组件
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp); // 附加到弹簧臂

	// 创建Niagara特效组件
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetupAttachment(SphereComp); // 附加到球体网格

	// 创建自定义移动组件
	MyMovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("MyMovementComponent"));
	MyMovementComponent->UpdatedComponent = RootComponent; // 设置移动更新的组件

	// 自动控制此pawn为玩家0
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// 游戏开始或pawn生成时调用
void ACollidePawn::BeginPlay()
{
	Super::BeginPlay();
}

// 每帧调用，处理帧更新逻辑
void ACollidePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 设置玩家输入绑定
void ACollidePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 设置增强输入系统映射上下文
	if (APlayerController* PlayerController = CastChecked<APlayerController>(GetController()))
	{
		// 获取本地玩家的增强输入子系统
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// 添加默认映射上下文
			Subsystem->AddMappingContext(MyMovementComponent->DefaultMappingContext, 0);
		}
	}

	// 设置输入绑定
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 将输入设置委托给移动组件
		MyMovementComponent->SetupInput(EnhancedInputComponent);
	}
}