// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
class TRUEPROJECT2_API AAbilitySystem : public AActor
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FeedBack", meta = (AllowPrivateAccess = "true"))
		class UData_AbilityFeedBackInfo* FeedBackContainer;

	// all abilities objects
		// Test
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbilityTest* AbilityTest;

		// Weapon Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_BasicPistol* AbilityPistol;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_Shotgun* AbilityShotgun;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_Sniper* AbilitySniper;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_Blade* AbilityBlade;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_AlienGun* Ability_AlienGun;

		// Bomb Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_BlackHoleBomb* Ability_BlackHoleBomb;

		// Hilo Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_WireTrap* Ability_WireTrap;
		// Shadow Category
		
		// Dimension Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_ReversePorjectiles* Ability_ReversePorjectiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_Teleport* Ability_Teleport;

		// Time Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_BulletTime* Ability_BulletTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_FForward* Ability_FForward;
	
	// Hacker Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_Paralyze* Ability_Paralyze;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_Open_Command* Ability_Open_Command;
	
	// Summoner Category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_Sum_MomFoot* Ability_Sum_MomFoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class AAbility_Sum_Rabbit* Ability_Sum_Rabbit;
		// Tool Category

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Check if abilitycode exist
	// REDO
	bool CheckAbility(int slot);

	// Call abilities to activate
	UData_AbilityFeedBackInfo* ActivateAbility(class UData_AbilityRequiredInfo* requiredInfo);
	
	// let ALUS processes feedback -> update all values
	// *************************************

	void CalculateCooldown(float PlayerFireRate, float WeaponFireRate);

	void ResetAllVariables();

	// Further function to each abilities
	// TP
	AAbility_Teleport* GetTPAbility();

};
