// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_GProjectileClass.h"
#include "Weapon_ReverseProjectile.generated.h"

UCLASS()
class LIMITLESS_API AWeapon_ReverseProjectile : public AWeapon_GProjectileClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_ReverseProjectile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		class AActor* Main;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	virtual void DoDamage(AActor* Actor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		float ExplotionRadius = 100.0f;

	virtual void DieEffect() override;

	virtual void ReachLocationEffect() override;

public:	

	UFUNCTION(BlueprintCallable)
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
