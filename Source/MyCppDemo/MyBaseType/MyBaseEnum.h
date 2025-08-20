#pragma once

#include "CoreMinimal.h"
#include "MyBaseEnum.generated.h"

UENUM(BlueprintType)
enum class EMYUENUM :uint8
{
	None,
	Base,
	Max
};