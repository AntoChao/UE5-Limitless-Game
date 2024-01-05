// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

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

#include "AbilitySystem.generated.h"

/* Abilities code (for now)
AbilityTest = 0

*/

/* Slots
0 -> Basic Attack
1 -> Ability 1
2 -> Ability 2
3 -> Ability 3
4 -> Ability 4
5 -> Passsive
*/

UCLASS(BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LIMITLESS_API AAbilitySystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilitySystem(const FObjectInitializer& ObjectInitializer);

protected:
	// Player
	UPROPERTY()
		class AMain* Player;

	UPROPERTY()
		TSubclassOf<class AMain> MainClass;

	UPROPERTY()
		class UWorld* GameWorld;
	
	// All abilities in array 
	UPROPERTY()
		TArray<int> AbilityList = {0, 11, 12, 13, 14, 15,
								21, 22, 23, 31, 41, 42, 51, 52, 53, 61, 
								62, 63, 71, 72, 73, 81, 82, 83, 91, 92, 93, 94};
	UPROPERTY()
		TArray<int> PassiveList = {};

	UPROPERTY()
		TArray<int> BasicAttackList = {0, 11, 12, 13, 14, 15};
	
	UPROPERTY()
		float DefAttackRate;

	// AbilityFeedBack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FeedBack" )
		class UData_AbilityFeedBackInfo* FeedBackContainer = nullptr;

	// all abilities objects
		// Test
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbilityTest> AbilityTestClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbilityTest* AbilityTest = nullptr;

		// Weapon Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_BasicPistol> AbilityPistolClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_BasicPistol* AbilityPistol = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_Shotgun> AbilityShotgunClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_Shotgun* AbilityShotgun = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_Sniper> AbilitySniperClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_Sniper* AbilitySniper = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_Blade> AbilityBladeClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_Blade* AbilityBlade = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_AlienGun> Ability_AlienGunClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_AlienGun* Ability_AlienGun = nullptr;

		// Bomb Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_BlackHoleBomb> Ability_BlackHoleBombClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_BlackHoleBomb* Ability_BlackHoleBomb = nullptr;

		// Hilo Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_WireTrap> Ability_WireTrapClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_WireTrap* Ability_WireTrap = nullptr;
		// Shadow Category
		
		// Dimension Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_ReversePorjectiles> Ability_ReversePorjectilesClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_ReversePorjectiles* Ability_ReversePorjectiles = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_Teleport> Ability_TeleportClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_Teleport* Ability_Teleport = nullptr;

		// Time Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_BulletTime> Ability_BulletTimeClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_BulletTime* Ability_BulletTime = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_FForward> Ability_FForwardClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_FForward* Ability_FForward = nullptr;
	
	// Hacker Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_Paralyze> Ability_ParalyzeClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_Paralyze* Ability_Paralyze = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_Open_Command> Ability_Open_CommandClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_Open_Command* Ability_Open_Command = nullptr;
	
	// Summoner Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_Sum_MomFoot> Ability_Sum_MomFootClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_Sum_MomFoot* Ability_Sum_MomFoot = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
		TSubclassOf<class AAbility_Sum_Rabbit> Ability_Sum_RabbitClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability" )
		class AAbility_Sum_Rabbit* Ability_Sum_Rabbit = nullptr;
		// Tool Category

public:
	// Check if abilitycode exist
	UFUNCTION()
		void SetPlayer(AMain* aplayer);
	UFUNCTION()
		void SetWorld(UWorld* currentWorld);

	UFUNCTION(BlueprintCallable, Category = "Effect")
		bool CheckAbility(int slot);

	// Call abilities to activate
	UData_AbilityFeedBackInfo* ActivateAbility(class UData_AbilityRequiredInfo* requiredInfo);
	
	UFUNCTION(BlueprintCallable, Category = "Effect")
		void CalculateCooldown(float PlayerFireRate, float WeaponFireRate);

	UFUNCTION(BlueprintCallable, Category = "Effect")
		void ResetAllVariables();

};
