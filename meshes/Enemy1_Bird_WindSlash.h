// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_GProjectileClass.h"
#include "Enemy1_Bird_WindSlash.generated.h"

/*
* Just a slash which has collision and deal damage to main if collide
*/
UCLASS()
class TRUEPROJECT2_API AEnemy1_Bird_WindSlash : public AWeapon_GProjectileClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy1_Bird_WindSlash();

protected:
	UPROPERTY(EditAnywhere)
		class AActor* Main;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Simulate Tick Function
	FTimerHandle TickSimulatorTimer;
	float TickSimulateTime = 0.1f;
	
	virtual void CustomTickFunction() override;

	float Damage;

public:	
	// bird spawn 2 WindSlashes, and the slash calculate the distance or projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector InitLocation;
	
	// a blueprint extend function to design the move by curves
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator SlashRotation;
	UFUNCTION(BlueprintCallable)
		void PermaRotate();

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
