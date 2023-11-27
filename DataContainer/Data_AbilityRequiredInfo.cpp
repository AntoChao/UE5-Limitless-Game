// Fill out your copyright notice in the Description page of Project Settings.


#include "Data_AbilityRequiredInfo.h"
#include "../All_Enemies/EnemyClass.h"
#include "../AbilitySystem/AbilitySystem.h"

// Weapons classes
#include "../meshes/Weapon_Blade.h"

/* 
	Sets default values
	FHitResult target, AActor* enemy, AWeapon_Blade* AWeapon,
	Also going to send the ability system, to separate some logic
	the player only need to know animation of each ability, the ability further container 
	should be part of the ability system
*/
void UData_AbilityRequiredInfo::InitializedAllAbilityInfo(UWorld* const World, EAbilityCode abilityNumber, 
									float frenzyAmount,float calmAmount, FVector location, 
									FRotator rotation, FHitResult target, 
									AMain* Player, AAbilitySystem* OneAbilitySystem)
{
	SetWorldPointer(World);
	SetAbilityCode(abilityNumber);
	SetPlayerFrenzy(frenzyAmount);
	SetPlayerCalm(calmAmount);
	SetPlayerLocation(location);
	SetPlayerRotation(rotation);
	SetHittenTarget(target);
	//SetEnemyTargetClass(enemy);
	SetPlayer(Player);
	SetAbilitySystem(OneAbilitySystem);
}

void UData_AbilityRequiredInfo::SetWorldPointer(UWorld* const World)
{
	worldObject = World;
}
UWorld* UData_AbilityRequiredInfo::GetWorldPointer()
{
	return worldObject;
}
void UData_AbilityRequiredInfo::SetAbilityCode(EAbilityCode abilityCo)
{
	abilityCode = abilityCo;
}
EAbilityCode UData_AbilityRequiredInfo::GetAbilityCode()
{
	return abilityCode;
}
void UData_AbilityRequiredInfo::SetPlayerFrenzy(float frenzyStat)
{
	playerFrenzy = frenzyStat;
}
float UData_AbilityRequiredInfo::GetPlayerFrenzy()
{
	return playerFrenzy;
}
void UData_AbilityRequiredInfo::SetPlayerCalm(float calmStat)
{
	playerCalm = calmStat;
}
float UData_AbilityRequiredInfo::GetPlayerCalm()
{
	return playerCalm;
}
void UData_AbilityRequiredInfo::SetPlayerLocation(FVector playerLocationStat)
{
	playerLocation = playerLocationStat;
}
FVector UData_AbilityRequiredInfo::GetPlayerLocation()
{
	return playerLocation;
}
void UData_AbilityRequiredInfo::SetPlayerRotation(FRotator playerRotationStat)
{
	playerRotation = playerRotationStat;
}
FRotator UData_AbilityRequiredInfo::GetPlayerRotation()
{
	return playerRotation;
}
void UData_AbilityRequiredInfo::SetHittenTarget(FHitResult hitResultStat)
{
	hitResult = hitResultStat;
}
FHitResult UData_AbilityRequiredInfo::GetHitResult()
{
	return hitResult;
}
void UData_AbilityRequiredInfo::SetPlayer(AMain* Character)
{
	PlayerCharacter = Character;
}
AMain* UData_AbilityRequiredInfo::GetPlayer()
{
	return PlayerCharacter;
}
void UData_AbilityRequiredInfo::SetAbilitySystem(AAbilitySystem* OneAbilitySystem)
{
	PlayerAbilitySystem = OneAbilitySystem;
}
AAbilitySystem* UData_AbilityRequiredInfo::GetAbilitySystem()
{
	return PlayerAbilitySystem;
}