// Fill out your copyright notice in the Description page of Project Settings.
#include "AbilitySystem.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// know AllCharacterClass main
#include "../AllCharactersClass.h"
#include "../Main.h"
// know individual abilities

// abilities to recognize
#include "../abilities/AbilityTest.h"
#include "../abilities/Ability_BasicPistol.h"
#include "../abilities/Ability_Shotgun.h"
#include "../abilities/Ability_Sniper.h"
#include "../abilities/Ability_Blade.h"
#include "../abilities/Ability_BlackHoleBomb.h"
#include "../abilities/Ability_AlienGun.h"
// BombBaiter
// Wall Breaker
#include "../abilities/Ability_WireTrap.h"
// ShadowSolder
// ShadowTravel
#include "../abilities/Ability_ReversePorjectiles.h"
#include "../abilities/Ability_Teleport.h"
// Switch dimention
#include "../abilities/Ability_BulletTime.h"
#include "../abilities/Ability_FForward.h"
#include "../abilities/Ability_Paralyze.h"
#include "../abilities/Ability_Open_Command.h"
// sum eagle
#include "../abilities/Ability_Sum_MomFoot.h"
#include "../abilities/Ability_Sum_Rabbit.h"


// container to recognize
#include "../DataContainer/Data_AbilityRequiredInfo.h"
#include "../DataContainer/Data_AbilityFeedBackInfo.h"

// Timer managment
#include "TimerManager.h"

// Sets default values
AAbilitySystem::AAbilitySystem(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FeedBackContainer = CreateDefaultSubobject<UData_AbilityFeedBackInfo>(TEXT("FeedBackContainer"));	

	
	AbilityTest = CreateDefaultSubobject<AAbilityTest>(TEXT("AAbilityTest"));
	AbilityPistol = CreateDefaultSubobject<AAbility_BasicPistol>(TEXT("AAbility_BasicPistol"));
	AbilityShotgun = CreateDefaultSubobject<AAbility_Shotgun>(TEXT("AAbility_Shotgun"));
	AbilitySniper = CreateDefaultSubobject<AAbility_Sniper>(TEXT("AAbility_Sniper"));
	AbilityBlade = CreateDefaultSubobject<AAbility_Blade>(TEXT("AAbility_Blade"));

	Ability_AlienGun = CreateDefaultSubobject<AAbility_AlienGun>(TEXT("AAbility_AlienGun"));
	Ability_BlackHoleBomb = CreateDefaultSubobject<AAbility_BlackHoleBomb>(TEXT("AAbility_BlackHoleBomb"));
	Ability_WireTrap = CreateDefaultSubobject<AAbility_WireTrap>(TEXT("AAbility_WireTrap"));
	Ability_ReversePorjectiles = CreateDefaultSubobject<AAbility_ReversePorjectiles>(TEXT("AAbility_ReversePorjectiles"));
	Ability_Teleport = CreateDefaultSubobject<AAbility_Teleport>(TEXT("AAbility_Teleport"));
	Ability_BulletTime = CreateDefaultSubobject<AAbility_BulletTime>(TEXT("AAbility_BulletTime"));
	Ability_FForward = CreateDefaultSubobject<AAbility_FForward>(TEXT("AAbility_FForward"));
	Ability_Paralyze = CreateDefaultSubobject<AAbility_Paralyze>(TEXT("AAbility_Paralyze"));
	Ability_Open_Command = CreateDefaultSubobject<AAbility_Open_Command>(TEXT("AAbility_Open_Command"));
	Ability_Sum_MomFoot = CreateDefaultSubobject<AAbility_Sum_MomFoot>(TEXT("AAbility_Sum_MomFoot"));
	Ability_Sum_Rabbit = CreateDefaultSubobject<AAbility_Sum_Rabbit>(TEXT("AAbility_Sum_Rabbit"));
}

void AAbilitySystem::BeginPlay()
{
	Super::BeginPlay();
}
/*
Check if the entered slot and abilityCode corresponde exist or corresponde
*/
bool AAbilitySystem::CheckAbility(int slot)
{
	return true;
}

void AAbilitySystem::CalculateCooldown(float PlayerFireRate, float WeaponFireRate)
{
	// may change the logarithms
	DefAttackRate = PlayerFireRate * WeaponFireRate;
}

UData_AbilityFeedBackInfo* AAbilitySystem::ActivateAbility(UData_AbilityRequiredInfo* requiredInfo)
{
	// INITIALIZE TO AVOID PROBLEM
	// bool exist, freUse, calUse, freGain, calGain, moveSpeedGain, XPGain
	FeedBackContainer->InitializedAllFeedBacks(false, 0, 0, 0, 0, 1.0f, 0);

	if (!requiredInfo->GetPlayer()->IsPlayerInAnimation())
	{
		// GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Player is ok to play animation"));
		switch (requiredInfo->GetAbilityCode())
		{
		case EAbilityCode::ETest:
		{
			if (IsValid(AbilityTest))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), AbilityTest->GetAbilityFireRate());

					FeedBackContainer = AbilityTest->Activate(requiredInfo);
					// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Using Ability Test"));
				}
			}
			break;
		}
		case EAbilityCode::EPistol:
		{
			if (IsValid(AbilityPistol))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, CritChance, CritMultiplier, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp
					AbilityPistol->CustomizeStatsPerAbility(5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), AbilityPistol->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("should do the Pistol animation"));
					FeedBackContainer = AbilityPistol->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::EShotgun:
		{
			// GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Ability is shotgun"));
			if (IsValid(AbilityShotgun))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					AbilityShotgun->CustomizeStatsPerAbility(20.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), AbilityShotgun->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = AbilityShotgun->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::ESniper:
		{
			if (IsValid(AbilitySniper))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					AbilitySniper->CustomizeStatsPerAbility(20.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f, 0);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), AbilitySniper->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = AbilitySniper->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::EBlade:
		{
			if (IsValid(AbilityBlade))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					AbilityBlade->CustomizeStatsPerAbility(5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 2.0f, 0.0f, 1.0f, 1.0f, 1);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), AbilityBlade->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = AbilityBlade->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::EAlienGun:
		{
			if (IsValid(Ability_AlienGun))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					Ability_AlienGun->CustomizeStatsPerAbility(5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_AlienGun->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_AlienGun->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::EBlackHoleBomb:
		{
			if (IsValid(Ability_BlackHoleBomb))
			{
				// Check player current weapon -> if is the bomb, then throw it, else set the bomb
				if (requiredInfo->GetPlayer()->GetCurrentAbilityInHand() == EAbilityCode::EBlackHoleBomb)
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					Ability_BlackHoleBomb->CustomizeStatsPerAbility(5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1);

					// Throw Bomb.
					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_BlackHoleBomb->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_BlackHoleBomb->Activate(requiredInfo);
				}
				else
				{
					// Set the main player weapon to the bomb -> turn to default ability when animation finished, 
					requiredInfo->GetPlayer()->SetCurrentAbilityInHand(EAbilityCode::EBlackHoleBomb);
				}
			}
			break;
		}
		case EAbilityCode::EBombBaiter:
		{
			/*
			if (IsValid(Ability_BlackHoleBomb))
			{
				// Check player current weapon -> if is the bomb, then throw it, else set the bomb
				if (requiredInfo->GetPlayer()->GetCurrentAbilityInHand() == EAbilityCode::EBlackHoleBomb)
				{
					// Throw Bomb.
					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), AbilityBlade->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_BlackHoleBomb->Activate(requiredInfo);
				}
				else
				{
					// Set the main player weapon to the bomb -> turn to default ability when animation finished, 
					requiredInfo->GetPlayer()->SetCurrentAbilityInHand(EAbilityCode::EBlackHoleBomb);
				}
			}
			*/
			break;
		}
		case EAbilityCode::EWallBreaker:
		{
			break;
		}
		case EAbilityCode::EWireTrap:
		{
			// Just need to customize abilities stats
			// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
			Ability_WireTrap->CustomizeStatsPerAbility(5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1);

			FeedBackContainer = Ability_WireTrap->Activate(requiredInfo);
			break;
		}
		case EAbilityCode::EShadowSolder:
		{
			FeedBackContainer = AbilityPistol->Activate(requiredInfo);
			break;
		}
		case EAbilityCode::EShadowTravel:
		{
			FeedBackContainer = AbilityPistol->Activate(requiredInfo);
			break;
		}
		case EAbilityCode::EReverseProjectiles:
		{
			if (IsValid(Ability_ReversePorjectiles))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					Ability_ReversePorjectiles->CustomizeStatsPerAbility(5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_ReversePorjectiles->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_ReversePorjectiles->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::ETeleport:
		{
			if (IsValid(Ability_Teleport))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					Ability_Teleport->CustomizeStatsPerAbility(5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Teleport->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_Teleport->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::ESwitchDimention:
		{
			FeedBackContainer = AbilityPistol->Activate(requiredInfo);
			break;
		}
		case EAbilityCode::EBulletTime:
		{
			if (IsValid(Ability_BulletTime))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					Ability_BulletTime->CustomizeStatsPerAbility(20.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f, 0);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_BulletTime->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_BulletTime->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::EFForward:
		{
			if (IsValid(Ability_FForward))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					Ability_FForward->CustomizeStatsPerAbility(20.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f, 0);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_FForward->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_FForward->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::EParalysis:
		{
			if (IsValid(Ability_Paralyze))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					Ability_Paralyze->CustomizeStatsPerAbility(5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Paralyze->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_Paralyze->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::EOpenCommand:
		{
			if (IsValid(Ability_Open_Command))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					Ability_Open_Command->CustomizeStatsPerAbility(5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Open_Command->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_Open_Command->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::ESumEagle:
		{
			/*
			if (IsValid(Ability_Open_Command))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Open_Command->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_Open_Command->Activate(requiredInfo);
				}
			}
			*/
			break;
		}
		case EAbilityCode::ESumBigFoot:
		{
			if (IsValid(Ability_Sum_MomFoot))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					Ability_Sum_MomFoot->CustomizeStatsPerAbility(5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Sum_MomFoot->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_Sum_MomFoot->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::ESumRabbit:
		{
			if (IsValid(Ability_Sum_Rabbit))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					// Just need to customize abilities stats
					// Dmg, fireRate, radio, duration, range, bSelfDmg, FrenCost, FrenRew, CaCost, CaRew, SpeRew, xp, type
					Ability_Sum_Rabbit->CustomizeStatsPerAbility(5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, false, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1);

					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Sum_Rabbit->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_Sum_Rabbit->Activate(requiredInfo);
				}
			}
			break;
		}
		case EAbilityCode::EItemBox:
		{
			/*
			if (IsValid(Ability_Open_Command))
			{
				if (IsValid(requiredInfo->GetPlayer()))
				{
					CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Open_Command->GetAbilityFireRate());

					requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
					FeedBackContainer = Ability_Open_Command->Activate(requiredInfo);
				}
			}
			*/
			break;
		}
		default:
		{
			break;
		}
		}
		return FeedBackContainer;
	}
	return FeedBackContainer;
}

// just in case if need to put some value to 0 or Null
void AAbilitySystem::ResetAllVariables()
{
	FeedBackContainer = CreateDefaultSubobject<UData_AbilityFeedBackInfo>(TEXT("FeedBackContainer"));

	AbilityTest = nullptr;
	AbilityPistol = nullptr;
	AbilityShotgun = nullptr;
	AbilitySniper = nullptr;
	AbilityBlade = nullptr;

	Ability_AlienGun = nullptr;
	Ability_BlackHoleBomb = nullptr;
	Ability_WireTrap = nullptr;
	// Need to create object of a TSubclass, as it has specified static mesh
	Ability_ReversePorjectiles = nullptr;	
	Ability_Teleport = nullptr;
	Ability_BulletTime = nullptr;
	Ability_FForward = nullptr;
	Ability_Paralyze = nullptr;
	Ability_Open_Command = nullptr;
	Ability_Sum_MomFoot = nullptr;
	Ability_Sum_Rabbit = nullptr;
}

// Further function to each abilities
// TP
AAbility_Teleport* AAbilitySystem::GetTPAbility()
{
	return Ability_Teleport;
}