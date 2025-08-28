

#include "PlayerPawnCase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// 设置默认值
APlayerPawnCase::APlayerPawnCase()
{
	// 设置此Pawn每帧调用Tick()。如果不需要，可以关闭以提高性能。
	PrimaryActorTick.bCanEverTick = true;

	// 创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// 创建静态网格组件
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	// 创建摄像机组件
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	// 创建弹簧臂组件
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	// 创建浮动Pawn移动组件
	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComp"));

	// 设置组件层级关系
	StaticMeshComp->SetupAttachment(RootComponent);
	SpringArmComp->SetupAttachment(StaticMeshComp);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	// 配置弹簧臂属性
	SpringArmComp->TargetArmLength = 400.0f; // 初始弹簧臂长度
	SpringArmComp->bEnableCameraLag = true; // 启用摄像机延迟
	SpringArmComp->CameraLagSpeed = 3.0f; // 摄像机延迟速度
	SpringArmComp->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f)); // 设置相对位置
	SpringArmComp->SocketOffset = FVector(0.0f, 0.0f, 200.0f); //设置插槽偏移 - 这将使摄像机位置相对于弹簧臂末端有一定偏移
	SpringArmComp->bUsePawnControlRotation = true; // 弹簧臂使用Pawn控制旋转

	// 配置摄像机属性
	CameraComp->bUsePawnControlRotation = false; // 摄像机不直接跟随控制器旋转

	// 自动拥有玩家0
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 禁用控制器旋转对Pawn旋转的影响
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
}

// 游戏开始或生成时调用
void APlayerPawnCase::BeginPlay()
{
	Super::BeginPlay();
	// 获取玩家控制器
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// 添加增强输入映射上下文
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// 处理移动输入
void APlayerPawnCase::Move(const FInputActionValue& Value)
{
	// 获取输入向量
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 获取控制器的Yaw旋转（忽略Pitch和Roll）
		FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

		// 根据控制器朝向计算前进和右方向量
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 应用移动输入
		AddMovementInput(ForwardDirection, MoveVector.Y); // 前后移动
		AddMovementInput(RightDirection, MoveVector.X); // 左右移动
	}
}

// 处理视角旋转输入
void APlayerPawnCase::Look(const FInputActionValue& Value)
{
	// 获取输入向量
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 获取当前控制器旋转
		FRotator CurrentRotation = Controller->GetControlRotation();

		// 计算新的俯仰角（上下看），限制在-80到80度之间
		float NewPitch = FMath::Clamp(CurrentRotation.Pitch + LookAxisVector.Y, -80.0f, 80.0f);

		// 计算新的偏航角（左右看）
		float NewYaw = CurrentRotation.Yaw + LookAxisVector.X;

		// 应用新的旋转，Roll固定为0
		Controller->SetControlRotation(FRotator(NewPitch, NewYaw, 0.0f));
	}
}

// 处理缩放输入
void APlayerPawnCase::Zoom(const FInputActionValue& Value)
{
	// 获取缩放输入值
	float ZoomValue = Value.Get<float>();

	// 计算新的弹簧臂长度
	float NewTargetArmLength = SpringArmComp->TargetArmLength + ZoomValue * ZoomSensitivity;

	// 限制弹簧臂长度在最小和最大值之间
	NewTargetArmLength = FMath::Clamp(NewTargetArmLength, MinZoomLength, MaxZoomLength);

	// 应用新的弹簧臂长度
	SpringArmComp->TargetArmLength = NewTargetArmLength;
}

// 每帧调用
void APlayerPawnCase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 此处可以添加每帧更新的逻辑
}

// 设置玩家输入组件
void APlayerPawnCase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 绑定增强输入动作
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 绑定移动动作
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPawnCase::Move);

		// 绑定视角动作
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerPawnCase::Look);

		// 绑定缩放动作
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerPawnCase::Zoom);
	}
}