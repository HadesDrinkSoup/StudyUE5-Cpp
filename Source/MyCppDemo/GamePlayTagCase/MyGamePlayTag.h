// 填写您的版权声明在项目设置的描述页面中

#pragma once

// 防止头文件重复包含

#include "CoreMinimal.h"
// 包含Unreal Engine核心最小头文件，提供基本类型和宏定义

#include "GameFramework/Actor.h"
// 包含Actor基类，所有可放置到场景中的对象都继承自此类

#include "MyTagType.h"
// 包含自定义标签类型头文件，可能包含特定的标签定义或类型声明

#include "GameplayTagAssetInterface.h"
// 包含Gameplay Tag资源接口，允许类拥有并管理Gameplay Tag

#include "MyGamePlayTag.generated.h"
// 包含Unreal Header Tool生成的反射代码，必须放在最后

// 声明一个Actor类，同时实现Gameplay Tag资源接口
// 这个类可以在场景中放置，并且能够管理和提供Gameplay Tag
UCLASS()
class MYCPPDEMO_API AMyGamePlayTag : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	// Unreal Header Tool生成的类体宏，必须出现在UCLASS类中

public:
	// 构造函数：设置此Actor的默认属性
	AMyGamePlayTag();

protected:
	// 受保护的方法区

	// 当游戏开始或Actor被生成时调用
	virtual void BeginPlay() override;

	// 实现IGameplayTagAssetInterface接口的方法
	// 用于获取此Actor拥有的所有Gameplay Tag
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

public:
	// 公有方法区

	// 每帧调用的更新函数
	virtual void Tick(float DeltaTime) override;

public:
	// 公有属性区

	// 可编辑的Gameplay Tag容器，用于存储和管理此Actor的标签
	// UPROPERTY宏使该属性在编辑器中可见、可编辑，并支持蓝图读写
	// Category = "MyTag" 表示在编辑器细节面板中显示在"MyTag"分类下
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MyTag")
	FGameplayTagContainer MyTagContainer;
	// 这个容器可以存储多个Gameplay Tag，用于标识Actor的类型、状态、能力等
	// 例如：可以添加"Enemy", "Boss", "Fire.Resistant"等标签来定义Actor特性
};