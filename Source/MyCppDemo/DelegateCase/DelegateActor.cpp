#include "DelegateCase/DelegateActor.h"
#include "Kismet/GameplayStatics.h"

// 构造函数：设置默认值
ADelegateActor::ADelegateActor()
{
    // 将此Actor设置为每帧调用Tick()。如果不需要，可以关闭以提高性能。
    PrimaryActorTick.bCanEverTick = false;
}

// 游戏开始或生成时调用
void ADelegateActor::BeginPlay()
{
    Super::BeginPlay();

    // 在场景中查找第一个AMyActor类的实例
    AActor* MyActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMyActor::StaticClass());

    // 将找到的Actor转换为AMyActor类型（如果转换失败会触发断言）
    MyActorRef = CastChecked<AMyActor>(MyActor);

    // 委托绑定代码（当前被注释掉）
    if (MyActorRef)
    {
        // 绑定无参数委托到无参数回调函数
        //MyActorRef->ScoreChangeDelegate.BindUObject(this, &ADelegateActor::OnScoreChange);

        // 绑定带参数委托到带参数回调函数
		int32 Health = 100;
        MyActorRef->ScoreChangeDelegate_OneParam.BindUObject(this, &ADelegateActor::OnScoreChange, Health);
    }
}

// 每帧调用
void ADelegateActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// 无参数的委托回调函数
void ADelegateActor::OnScoreChange()
{
    // 当分数变化时，调用MyActor的打印分数方法
    if (MyActorRef)
    {
        MyActorRef->PrintScore();
    }
}

// 带参数的委托回调函数
// @param Score - 传递的分数值（虽然未使用，但委托签名需要）
void ADelegateActor::OnScoreChange(int32 Score, int32 Health)
{
    // 当分数变化时，调用MyActor的打印分数方法
    // 注意：这里没有使用传入的Score参数，只是调用了相同的打印方法
    if (MyActorRef)
    {
        MyActorRef->PrintScore();
    }
}