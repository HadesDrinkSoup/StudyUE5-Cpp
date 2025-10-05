// 填写您的版权声明在项目设置的描述页面中

#include "GamePlayTagCase/MyGamePlayTag.h"

// 定义一个静态的游戏玩法标签，表示"毒系魔法"技能
// 使用 UE_DEFINE_GAMEPLAY_TAG_STATIC 宏创建编译时常量的游戏标签
// 这个标签可以在整个模块中使用，但不会在模块外暴露
UE_DEFINE_GAMEPLAY_TAG_STATIC(Skill_Magic_Poison, "Skill.Magic.Poison")
// 标签结构说明：
// - "Skill": 技能大类
// - "Magic": 魔法子类  
// - "Poison": 毒系具体类型

// 类构造函数：设置默认值
AMyGamePlayTag::AMyGamePlayTag()
{
	// 设置此Actor每帧调用Tick()函数
	// 如果不需要每帧更新，可以关闭此项以提高性能
	PrimaryActorTick.bCanEverTick = true;

	// 注意：这里没有初始化MyTagContainer，因为它会使用默认的空容器
	// 可以在构造函数中添加初始标签，例如：
	// MyTagContainer.AddTag(Skill_Magic_Poison);
}

// 游戏开始或Actor被生成时调用
void AMyGamePlayTag::BeginPlay()
{
	// 将"木系魔法"标签添加到标签容器中
	// 这通常在游戏开始时初始化Actor的标签状态
	MyTagContainer.AddTag(Skill_Magic_Wood);

	// 调用父类的BeginPlay方法，确保继承链上的初始化逻辑正确执行
	Super::BeginPlay();

	// 此时Actor已经拥有了"Skill.Magic.Wood"标签
	// 其他系统可以通过GetOwnedGameplayTags方法查询到这个标签
}

// 实现IGameplayTagAssetInterface接口的方法
// 用于获取此Actor拥有的所有游戏玩法标签
void AMyGamePlayTag::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	// 将MyTagContainer中的所有标签追加到传入的TagContainer参数中
	// 这允许外部系统查询此Actor拥有的所有标签
	TagContainer.AppendTags(MyTagContainer);

	// 使用示例：
	// FGameplayTagContainer OutTags;
	// MyActor->GetOwnedGameplayTags(OutTags);
	// 然后可以检查OutTags中是否包含特定标签
}

// 每帧调用的更新函数
void AMyGamePlayTag::Tick(float DeltaTime)
{
	// 调用父类的Tick方法
	Super::Tick(DeltaTime);

	// 可以在这里添加每帧需要执行的逻辑
	// 例如：检查标签状态的变化，根据标签触发特定行为等

	// 示例用法：
	// if (MyTagContainer.HasTag(Skill_Magic_Wood)) {
	//     // 执行木系魔法特有的每帧逻辑
	// }
}