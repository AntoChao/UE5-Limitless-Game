// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Main.h"
#include "Data_AbilityRequiredInfo.generated.h"


// container should not have any logic operation, only a container that contains infos


/*
Ability Info:
	requirement:
		Player:
			- Player frenzy
			- Player calm
			- Player basicAttack chosen -> some ability will require specific basicAttack
			- Player location
			- Player rotation

		HittenObject/ Line trace:
			ONLY FHITRESULT, THE ABILITY IDENTIFY IF IT IS AN ENEMY OR DOOR OR NULL...

			useless:
				Enemy info -> NULL/ exist
					- location
					- rotation
					- target health -> maybe for some execution
					- target player controller -> por posession in hacker

				Other info -> NULL/ exist
					- Hitten location -> for tp/ bullet/ boom

*/

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRUEPROJECT2_API UData_AbilityRequiredInfo : public UDataAsset
{
	GENERATED_BODY()

private:
	// all stats container
	UWorld* worldObject;
	EAbilityCode abilityCode; // for ability system call its activate
	float playerFrenzy;
	float playerCalm;
	FVector playerLocation;
	FRotator playerRotation;

	// FHitResult -> the acctor which the line trace impact, could be null, enemy or aactor
	// for all abilities that need get hitten info, allow to access hitten location and acctor
	FHitResult hitResult; // chould be change to hitresult

	UPROPERTY(EditAnywhere, Category = "Player")
		class AMain* PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "Ability System")
		class AAbilitySystem* PlayerAbilitySystem;


public:
	// create a InitliziedALLValue in order to simplify sets
	void InitializedAllAbilityInfo(UWorld* const World, EAbilityCode abilityNumber, float frenzyAmount, float calmAmount,
		FVector location, FRotator rotation, FHitResult target, AMain* Player, AAbilitySystem* OneAbilitySystem);

	// Setters/ Getters of all information
	void SetWorldPointer(UWorld* const World);
	void SetAbilityCode(EAbilityCode abilityCo);
	void SetPlayerFrenzy(float frenzyStat);
	void SetPlayerCalm(float calmStat);
	void SetPlayerLocation(FVector playerLocationStat);
	void SetPlayerRotation(FRotator playerRotationStat);
	void SetHittenTarget(FHitResult hitResultStat);
	//void SetEnemyTargetClass(AActor* enemy);
	void SetPlayer(AMain* Character);
	void SetAbilitySystem(AAbilitySystem* AbilitySystem);

	UWorld* GetWorldPointer();
	EAbilityCode GetAbilityCode();
	float GetPlayerFrenzy();
	float GetPlayerCalm();
	FVector GetPlayerLocation();
	FRotator GetPlayerRotation();
	FHitResult GetHitResult();
	//AActor* GetEnemyTargetClass();
	AMain* GetPlayer();
	AAbilitySystem* GetAbilitySystem();
};