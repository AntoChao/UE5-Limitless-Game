// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_GProjectileClass.h"
#include "Weapon_Gem.generated.h"

UCLASS()
class LIMITLESS_API AWeapon_Gem : public AWeapon_GProjectileClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Gem();

protected:
	UPROPERTY(EditAnywhere)
		class AMain* Main;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void CustomTickFunction() override;

public:	

	UFUNCTION(BlueprintCallable)
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	virtual void ReachLocationEffect() override;

};
