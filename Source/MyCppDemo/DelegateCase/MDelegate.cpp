#include "DelegateCase/MDelegate.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

// 构造函数：设置默认值
AMDelegate::AMDelegate()
{
    // 禁用Tick函数以提高性能（不需要每帧更新）
    PrimaryActorTick.bCanEverTick = false;
}

// 游戏开始时调用：初始化委托绑定
void AMDelegate::BeginPlay()
{
    Super::BeginPlay();

    // 查找世界中所有的AMyActor实例
    TArray<AActor*> MyActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyActor::StaticClass(), MyActors);

    // 遍历所有找到的AMyActor实例
    for (AActor* Actor : MyActors)
    {
        AMyActor* MyActor = Cast<AMyActor>(Actor);
        if (MyActor)
        {
            // 为每个AMyActor实例绑定多播委托到当前对象的OnScoreChange方法
            MyActor->ScoreChangeMulticastDelegate.AddUObject(this, &AMDelegate::OnScoreChange);

            // 保存引用到数组，便于后续管理和清理
            MyActorRefs.Add(MyActor);
        }
    }
}

// 游戏结束或Actor被销毁时调用：清理委托绑定
void AMDelegate::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // 遍历所有保存的MyActor引用
    for (AMyActor* MyActor : MyActorRefs)
    {
        // 检查Actor是否有效且委托是否已绑定
        if (MyActor && MyActor->ScoreChangeMulticastDelegate.IsBound())
        {
            // 移除当前对象绑定的所有委托（防止内存泄漏）
            MyActor->ScoreChangeMulticastDelegate.RemoveAll(this);
        }
    }

    // 清空引用数组
    MyActorRefs.Empty();
}

// 每帧调用（但在此类中被禁用）
void AMDelegate::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// 修改所有MyActor实例的分数（可在蓝图中调用）
void AMDelegate::ChangeScore()
{
    // 遍历所有保存的MyActor引用
    for (AMyActor* MyActor : MyActorRefs)
    {
        if (MyActor)
        {
            // 为每个MyActor设置一个0-100的随机分数
            // 这会触发SetScore方法，进而触发委托
            MyActor->SetScore(FMath::Rand() % 101);
        }
    }
}

// 委托回调函数：当任何MyActor分数变化时被调用
void AMDelegate::OnScoreChange()
{
    // 注意：这里只是响应分数变化，不要再次触发分数修改或打印
    // 使用UE_LOG输出日志到控制台
    UE_LOG(LogTemp, Log, TEXT("收到分数变化通知"));
}