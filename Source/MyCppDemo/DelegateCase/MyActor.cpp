#include "DelegateCase/MyActor.h"
#include "Engine/Engine.h"

// 构造函数：设置默认值
AMyActor::AMyActor()
{
    PrimaryActorTick.bCanEverTick = true;
    PlayerId = FGuid::NewGuid();
    Score = 0;
}

void AMyActor::BeginPlay()
{
    Super::BeginPlay();
    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    }
    PrintScore();
}

void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyActor::SetScore(int32 NewScore)
{
    if (Score == NewScore)
    {
        return;
    }

    Score = NewScore;

    // 执行各种委托
    /*
    // 检查并执行单播委托（无参数）
    if (ScoreChangeDelegate.IsBound())
    {
        ScoreChangeDelegate.Execute();
    }

    // 检查并执行带参数的单播委托，传入当前分数值
    if (ScoreChangeDelegate_OneParam.IsBound())
    {
        ScoreChangeDelegate_OneParam.Execute(Score);
    }

    // 检查并广播多播委托（通知所有绑定的函数）
    if (ScoreChangeMulticastDelegate.IsBound())
    {
        ScoreChangeMulticastDelegate.Broadcast();
    }
    */

    
}

void AMyActor::PrintScore()
{
    // 广播动态多播委托（蓝图可绑定）
    if (OnScoreChanged.IsBound())
    {
        OnScoreChanged.Broadcast(Score);
    }
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            5.f,
            FColor::Yellow,
            FString::Format(
                TEXT("玩家PlayerId {0} 当前分数: {1}"),  // 格式化字符串
                {
                    PlayerId.ToString(),         // 玩家ID字符串
                    FString::FromInt(Score)      // 分数转换为字符串
                }
            )
        );
    }
}