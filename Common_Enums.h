// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common_Enums.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EGamePlayState : uint8
{
	EPreparing,
	EPlaying,
	EGameOver
};

UENUM(BlueprintType, Blueprintable)
enum class EGameOverReason : uint8
{
	ETrueEnding,
	EFalseEnding,
	EFailMission,
	ETimeFreezed,
	EEmbraceVoid
};

// A ENUM THAT REPRESENT ALL ABILITIES: INCLUDING WEAPON -> replace ability code
UENUM(BlueprintType, Blueprintable)
enum class EAbilityCode : uint8
{
	ENone,
	ETest,
	EPistol,
	EShotgun,
	ESniper,
	EBlade,
	EBlackHoleBomb,
	EAlienGun,
	EBombBaiter,
	EWallBreaker,
	EWireTrap,
	EShadowSolder,
	EShadowTravel,
	EReverseProjectiles,
	ETeleport,
	ESwitchDimention,
	EBulletTime,
	EFForward,
	EParalysis,
	EOpenCommand,
	ESumEagle,
	ESumBigFoot,
	ESumRabbit,
	EItemBox,
	EUnknown
};

UENUM(BlueprintType, Blueprintable)
enum class EObjectiveStatus : uint8
{
	EUndiscovered,
	EDiscovered,
	EFinished,
	EUnknown
};

UENUM(BlueprintType, Blueprintable)
enum class ELanguageSelected : uint8
{
	English,
	Chinese,
	Spanish
};

UENUM(BlueprintType, Blueprintable)
enum class EFloorType : uint8
{
	EConcrete,
	EGlass,
	EDirt,
	ESand
};

UENUM(BlueprintType, Blueprintable)
enum class EEnemyRarity : uint8
{
	ENormal,
	ESpecial,
	EElite,
	EBoss,
	EGigaBoss,
	EUnknown
};

UCLASS()
class LIMITLESS_API ACommon_Enums : public AActor
{
	GENERATED_BODY()

public:
	ACommon_Enums();
};
