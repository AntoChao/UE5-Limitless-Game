// Fill out your copyright notice in the Description page of Project Settings.
#include "AbilitySystem.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// know AllCharacterClass main
#include "../AllCharactersClass.h"
#include "../Main.h"

// container to recognize
#include "../DataContainer/Data_AbilityRequiredInfo.h"
#include "../DataContainer/Data_AbilityFeedBackInfo.h"

// Timer managment
#include "TimerManager.h"

// Sets default values
AAbilitySystem::AAbilitySystem(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {
	
	FeedBackContainer = CreateDefaultSubobject<UData_AbilityFeedBackInfo>(TEXT("FeedBackContainer"));
}

/*
Check if the entered slot and abilityCode corresponde exist or corresponde
*/
bool AAbilitySystem::CheckAbility(int slot) {
	return true;
}

void AAbilitySystem::CalculateCooldown(float PlayerFireRate, float WeaponFireRate) {
	// may change the logarithms
	DefAttackRate = PlayerFireRate * WeaponFireRate;
}

UData_AbilityFeedBackInfo* AAbilitySystem::ActivateAbility(UData_AbilityRequiredInfo* requiredInfo) {
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// INITIALIZE TO AVOID PROBLEM
	// bool exist, freUse, calUse, freGain, calGain, moveSpeedGain, XPGain
	/*FeedBackContainer = NewObject<UData_AbilityFeedBackInfo>(this,
		UData_AbilityFeedBackInfo::StaticClass());*/

	FeedBackContainer->InitializedAllFeedBacks(false, 0, 0, 0, 0, 1.0f, 0);

	if (!requiredInfo->GetPlayer()->IsPlayerInAnimation())	{
		switch (requiredInfo->GetAbilityCode()){
			case EAbilityCode::ETest: {
				if (IsValid(AbilityTestClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {

						AbilityTest = requiredInfo->GetWorldPointer()->SpawnActor<AAbilityTest>(AbilityTestClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), AbilityTest->GetAbilityFireRate());

						if (IsValid(AbilityTest)) {
							FeedBackContainer = AbilityTest->Activate(requiredInfo);
							AbilityTest->Destroy();
						}
						
					}
				}
				break;
			}
			case EAbilityCode::EPistol: {
				if (IsValid(AbilityPistolClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {
						
						AbilityPistol = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_BasicPistol>(AbilityPistolClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), AbilityPistol->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(AbilityPistol)) {
							FeedBackContainer = AbilityPistol->Activate(requiredInfo);
							AbilityPistol->Destroy();
						}
					}
				}
				break;
			}
			case EAbilityCode::EShotgun: {
				if (IsValid(AbilityShotgunClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {

						AbilityShotgun = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_Shotgun>(AbilityShotgunClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), AbilityShotgun->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(AbilityShotgun)) {
							FeedBackContainer = AbilityShotgun->Activate(requiredInfo);
							AbilityShotgun->Destroy();
						}
					}
				}
				break;
			}
			case EAbilityCode::ESniper: {
				if (IsValid(AbilitySniperClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {
						
						AbilitySniper = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_Sniper>(AbilitySniperClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), AbilitySniper->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(AbilitySniper)) {
							FeedBackContainer = AbilitySniper->Activate(requiredInfo);
							AbilitySniper->Destroy();
						}
						
					}
				}
				break;
			}
			case EAbilityCode::EBlade: {
				if (IsValid(AbilityBladeClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {
						/*
						AbilityBlade = requiredInfo->GetWorldPointer()->SpawnActor<AAbilityBlade>(AbilityBladeClass,
							FTransform::Identity, ActorSpawnParams);
						*/
						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), AbilityBlade->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(AbilityBlade)) {
							FeedBackContainer = AbilityBlade->Activate(requiredInfo);
							AbilityBlade->Destroy();
						}
						
					}
				}
				break;
			}
			case EAbilityCode::EAlienGun: {
				if (IsValid(Ability_AlienGunClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {

						Ability_AlienGun = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_AlienGun>(Ability_AlienGunClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_AlienGun->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(Ability_AlienGun)) {
							FeedBackContainer = Ability_AlienGun->Activate(requiredInfo);
							Ability_AlienGun->Destroy();
						}
						
					}
				}
				break;
			}
			case EAbilityCode::EBlackHoleBomb: {
				if (IsValid(Ability_BlackHoleBombClass)) {
					// Check player current weapon -> if is the bomb, then throw it, else set the bomb
					if (requiredInfo->GetPlayer()->GetCurrentAbilityInHand() == EAbilityCode::EBlackHoleBomb) {
						
						Ability_BlackHoleBomb = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_BlackHoleBomb>(Ability_BlackHoleBombClass,
							FTransform::Identity, ActorSpawnParams);

						// Throw Bomb.
						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_BlackHoleBomb->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(Ability_BlackHoleBomb)) {
							FeedBackContainer = Ability_BlackHoleBomb->Activate(requiredInfo);
							Ability_BlackHoleBomb->Destroy();
						}
						
					}
					else {
						// Set the main player weapon to the bomb -> turn to default ability when animation finished, 
						requiredInfo->GetPlayer()->SetCurrentAbilityInHand(EAbilityCode::EBlackHoleBomb);
					}
				}
				break;
			}
			case EAbilityCode::EBombBaiter: {
				break;
			}
			case EAbilityCode::EWallBreaker: {
				break;
			}
			case EAbilityCode::EWireTrap: {
				
				FeedBackContainer = Ability_WireTrap->Activate(requiredInfo);
				break;
			}
			case EAbilityCode::EShadowSolder: {
				FeedBackContainer = AbilityPistol->Activate(requiredInfo);
				break;
			}
			case EAbilityCode::EShadowTravel: {
				FeedBackContainer = AbilityPistol->Activate(requiredInfo);
				break;
			}
			case EAbilityCode::EReverseProjectiles: {
				if (IsValid(Ability_ReversePorjectilesClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {
						
						Ability_ReversePorjectiles = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_ReversePorjectiles>(
							Ability_ReversePorjectilesClass, FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_ReversePorjectiles->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(Ability_ReversePorjectiles)) {
							FeedBackContainer = Ability_ReversePorjectiles->Activate(requiredInfo);
							Ability_ReversePorjectiles->Destroy();
						}
						
					}
				}
				break;
			}
			case EAbilityCode::ETeleport: {
				if (IsValid(Ability_TeleportClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {

						Ability_Teleport = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_Teleport>(Ability_TeleportClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Teleport->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(Ability_Teleport)) {
							FeedBackContainer = Ability_Teleport->Activate(requiredInfo);
							Ability_Teleport->Destroy();
						}
					}
				}
				break;
			}
			case EAbilityCode::ESwitchDimention: {
				FeedBackContainer = AbilityPistol->Activate(requiredInfo);
				break;
			}
			case EAbilityCode::EBulletTime: {
				if (IsValid(Ability_BulletTimeClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {
						
						Ability_BulletTime = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_BulletTime>(Ability_BulletTimeClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_BulletTime->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(Ability_BulletTime)) {
							FeedBackContainer = Ability_BulletTime->Activate(requiredInfo);
							Ability_BulletTime->Destroy();
						}
						
					}
				}
				break;
			}
			case EAbilityCode::EFForward: {
				if (IsValid(Ability_FForwardClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {
						
						Ability_FForward = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_FForward>(Ability_FForwardClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_FForward->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(Ability_FForward)) {
							FeedBackContainer = Ability_FForward->Activate(requiredInfo);
							Ability_FForward->Destroy();
						}
						
					}
				}
				break;
			}
			case EAbilityCode::EParalysis: {
				if (IsValid(Ability_ParalyzeClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {
						
						Ability_Paralyze = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_Paralyze>(Ability_ParalyzeClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Paralyze->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(Ability_Paralyze)) {
							FeedBackContainer = Ability_Paralyze->Activate(requiredInfo);
							Ability_Paralyze->Destroy();
						}
						
					}
				}
				break;
			}
			case EAbilityCode::EOpenCommand: {
				if (IsValid(Ability_Open_CommandClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {
						
						Ability_Open_Command = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_Open_Command>(Ability_Open_CommandClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Open_Command->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(Ability_Open_Command)) {
							FeedBackContainer = Ability_Open_Command->Activate(requiredInfo);
							Ability_Open_Command->Destroy();
						}
						
					}
				}
				break;
			}
			case EAbilityCode::ESumEagle: {
				
				break;
			}
			case EAbilityCode::ESumBigFoot: {
				if (IsValid(Ability_Sum_MomFootClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {
						
						Ability_Sum_MomFoot = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_Sum_MomFoot>(Ability_Sum_MomFootClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Sum_MomFoot->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						if (IsValid(Ability_Sum_MomFoot)) {
							FeedBackContainer = Ability_Sum_MomFoot->Activate(requiredInfo);
							Ability_Sum_MomFoot->Destroy();
						}
					}
				}
				break;
			}
			case EAbilityCode::ESumRabbit: {
				if (IsValid(Ability_Sum_RabbitClass)) {
					if (IsValid(requiredInfo->GetPlayer())) {
						
						Ability_Sum_Rabbit = requiredInfo->GetWorldPointer()->SpawnActor<AAbility_Sum_Rabbit>(Ability_Sum_RabbitClass,
							FTransform::Identity, ActorSpawnParams);

						CalculateCooldown(requiredInfo->GetPlayer()->GetPlayerAttackRate(), Ability_Sum_Rabbit->GetAbilityFireRate());

						requiredInfo->GetPlayer()->PlayMontages(requiredInfo->GetAbilityCode(), DefAttackRate);
						
						if (IsValid(Ability_Sum_Rabbit)) {
							FeedBackContainer = Ability_Sum_Rabbit->Activate(requiredInfo);
							Ability_Sum_Rabbit->Destroy();
						}
						
					}
				}
				break;
			}
			case EAbilityCode::EItemBox: {
				break;
			}
			default: {
				break;
			}
		}
		return FeedBackContainer;
	}
	return FeedBackContainer;
}

// just in case if need to put some value to 0 or Null
void AAbilitySystem::ResetAllVariables() {
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

void AAbilitySystem::SetPlayer(AMain* aplayer) {
	Player = aplayer;
}
void AAbilitySystem::SetWorld(UWorld* currentWorld) {
	GameWorld = currentWorld;
}