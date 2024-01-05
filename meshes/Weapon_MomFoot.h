// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_GProjectileClass.h"
#include "Weapon_MomFoot.generated.h"

UCLASS()
class LIMITLESS_API AWeapon_MomFoot : public AWeapon_GProjectileClass
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon_MomFoot();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ReachLocationEffect();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Reach Location Effect")
		void Spawn_ReachLocationEffects();
public:
	UFUNCTION(BlueprintCallable)
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
