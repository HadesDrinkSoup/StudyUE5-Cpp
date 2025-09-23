#include "DelegateCase/MyActor.h"
#include "Engine/Engine.h"

// 构造函数：设置默认值
AMyActor::AMyActor()
{
    // 允许Actor每帧调用Tick函数
    PrimaryActorTick.bCanEverTick = true;

    // 生成唯一的玩家ID
    PlayerId = FGuid::NewGuid();

    // 初始化分数为0
    Score = 0;
}

// 游戏开始时调用
void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    // 如果没有根组件，创建一个场景组件作为根组件
    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    }
}

// 每帧调用的函数
void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// 设置分数并触发相关委托
// @param NewScore - 新的分数值
void AMyActor::SetScore(int32 NewScore)
{
    // 更新分数值
    Score = NewScore;

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

    // 在屏幕上显示分数信息
    PrintScore();
}

// 在屏幕上打印当前分数信息
void AMyActor::PrintScore()
{
    // 确保引擎有效
    if (GEngine)
    {
        // 在屏幕上显示调试信息，持续5秒，黄色字体
        GEngine->AddOnScreenDebugMessage(
            -1,                                   // 使用-1自动分配消息ID
            5.f,                                  // 显示5秒
            FColor::Yellow,                       // 黄色文字
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