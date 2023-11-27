// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common_Enums.generated.h"

UENUM()
enum class EGamePlayState
{
	EPreparing,
	EPlaying,
	EGameOver
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
	EEnglish,
	EChinese,
	ESpanish,
	EUnknown
};

UENUM(BlueprintType, Blueprintable)
enum class EDamageColor : uint8
{
	ERed,
	ERedPurple,
	ERedBlack,
	EUnknown
};

UCLASS()
class TRUEPROJECT2_API ACommon_Enums : public AActor
{
	GENERATED_BODY()

public:
	ACommon_Enums();
};

UENUM()
enum class EFloorType
{
	EConcrete,
	EGlass,
	EDirt,
	ESand
};

UENUM()
enum class EEnemyRarity
{
	ENormal,
	ESpecial,
	EElite,
	EBoss,
	EGigaBoss,
	EUnknown
};
