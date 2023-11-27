// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_GProjectileClass.h"
#include "Weapon_BlackHoleBomb.generated.h"

/*
The bomb is just a bomb which after X segs, it started to pull over every one 
in X radius toward its
*/
UCLASS()
class TRUEPROJECT2_API AWeapon_BlackHoleBomb : public AWeapon_GProjectileClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_BlackHoleBomb();

	UFUNCTION(BlueprintCallable)
		UProjectileMovementComponent* GetWeaponProjectileCompMovement();

	UFUNCTION(BlueprintCallable)
		USkeletalMeshComponent* GetWeaponSkeleton();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
		class AActor* Main;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	virtual void CustomTickFunction() override;

	// BlackHoleEffect -> start at the beginning to the end
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Black Hole")
		TArray<class AEnemyClass*> EnemiesToPull = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Black Hole")
		float PullStrength = 3000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Black Hole")
		float PullDuration = 3.0f;

	UFUNCTION(BlueprintCallable)
		void PullOverlappedEnemies();
	// void PullInitialEnemies();
	UFUNCTION(BlueprintCallable)
		void BlackHoleEffect(AEnemyClass* AEnemy);

	// Die effect is just an explotion of blackhole
	virtual void DieEffect() override;
	virtual void DoDamage() override;

	virtual void ReachLocationEffect() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void PhysicsFunc();

};
