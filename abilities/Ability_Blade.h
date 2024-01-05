// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "../meshes/Weapon_Blade.h"
#include "Ability_Blade.generated.h"

UCLASS()
class LIMITLESS_API AAbility_Blade : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_Blade(const class FObjectInitializer& ObjectInitializer);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AWeapon_Blade* WeaponBlade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FeedBack", meta = (AllowPrivateAccess = "true"))
		class UData_AbilityRequiredInfo* requiredInfoContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		class AActor* Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSet<AActor*> EnemyList = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSubclassOf<class AEnemyClass> EnemyClass;

	FTimerHandle ApplyEffectTimer;

public:	
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;


};
