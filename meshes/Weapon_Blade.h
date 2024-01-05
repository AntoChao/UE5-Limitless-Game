// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_GeneralClass.h"
#include "Weapon_Blade.generated.h"

UCLASS()
class LIMITLESS_API AWeapon_Blade : public AWeapon_GeneralClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Blade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSet<AActor*> EnemyHitten = {};
		//TSet<ABasicEnemy*> EnemyHitten = {};
		
	// declare animation and sound -> then apply then to parent funcion playanimation and play sound
public:
	virtual void DoDamage(AActor* Actor) override;

	void usingBlade(bool modifier);
	
	TSet<AActor*> ReturnHittenEnemies();
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	// declare overlap end function
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
