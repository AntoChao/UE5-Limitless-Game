// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralAbilityClass.h"
#include "Ability_Sum_MomFoot.generated.h"

/*
This ability is just to spawm a black hole bomb with corresponding functionality
*/

UCLASS()
class LIMITLESS_API AAbility_Sum_MomFoot : public AGeneralAbilityClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility_Sum_MomFoot(const class FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomFoot Class")
		TSubclassOf<class AWeapon_MomFoot> AWeapon_MomFootClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomFoot Class")
		AWeapon_MomFoot* MomFoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomFoot Class")
		FVector SmashOrientation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomFoot Class")
		float SmashFoce;

	UFUNCTION(BlueprintCallable, Category = "Foot")
		void SpawnFoot(UData_AbilityRequiredInfo* requiredInfo);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomFoot Class")
		float MomFootHeight = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace Check")
		FHitResult LineTraceHit;
	UFUNCTION(BlueprintCallable, Category = "Line Trace Check")
		bool ShotTheLineTraceCheck(FVector HitLocation);

public:	

	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) override;
};
