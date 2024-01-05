// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../components/DamageComponent.h"
#include "Sound/SoundCue.h"
#include "Weapon_GeneralClass.generated.h"

/* Animation and sound should be part of the weapon
* because the weapon is the one who fire and make sound...
*/
UCLASS()
class LIMITLESS_API AWeapon_GeneralClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon_GeneralClass();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionComponent")
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class USkeletalMeshComponent* Body;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionComponent")
		class USphereComponent* EffectArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AActor* Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FHitResult MyHit;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool beingUsed;

	UPROPERTY(EditAnywhere)
		class AMainController* MainController;

	UPROPERTY(EditAnywhere)
		class AAIEnemyClassController* EnemyController;

	// Simulate Tick Function
	FTimerHandle TickSimulatorTimer;
	float TickSimulateTime = 0.1f;

	// Owner -> in order to separate if the waepon is enemies of main
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool OwnByMain = false;

	// only call it in begin play if it is necessary
	UFUNCTION(BlueprintCallable)
		virtual void CustomTickFunction();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDamageComponent* DamageComponent;

	/***********************************************************************
	LIFESPAM AND DIE EFFECT
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle LifeSpanTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LifeSpan;
	// just create the timer
	UFUNCTION(BlueprintCallable)
		void StartDieTimer();
	UFUNCTION(BlueprintCallable)
		virtual void DieEffect();
	UFUNCTION(BlueprintCallable)
		virtual void Die();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* AnimMontage_SpawnEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* AnimMontage_DieEffect;

	UFUNCTION(BlueprintCallable)
		virtual void DoDamage(AActor* Actor);

public:
	UFUNCTION(BlueprintCallable)
		bool WeaponOwnedByMain();

	UFUNCTION(BlueprintCallable)
		void SetMainController(AMainController* AMainController);
	UFUNCTION(BlueprintCallable)
		void SetEnemyController(AAIEnemyClassController* AEnemyController);

	// common functions 
	UFUNCTION(BlueprintCallable)
		void SetDamage(float aDamageValue);

	// others animation should be call directly by Animation blueprint and not class
	UFUNCTION(BlueprintCallable)
		void PlaySpawnAnimation();
	UFUNCTION(BlueprintCallable)
		void OnSpawnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION(BlueprintCallable)
		void PlayEndAnimation();
	UFUNCTION(BlueprintCallable)
		void OnDieMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void isUsingWeapon(bool modifier);
};
