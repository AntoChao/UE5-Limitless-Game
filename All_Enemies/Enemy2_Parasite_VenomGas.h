// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy2_Parasite_VenomGas.generated.h"

/*
* Just a slash which has collision and deal damage to main if collide
*/
UCLASS()
class LIMITLESS_API AEnemy2_Parasite_VenomGas : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy2_Parasite_VenomGas();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "CollisionComponent")
		class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USkeletalMeshComponent* Body;

	UPROPERTY(EditAnywhere)
		class AActor* Main;

	UPROPERTY(EditAnywhere)
		FHitResult MyHit;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Life Spam
	FTimerHandle LifeSpamTimer;
	float LifeSpamTime = 10.0f;
	void VenomDesapear();

	// Simulate Tick Function
	FTimerHandle TickSimulatorTimer;
	float TickSimulateTime = 0.1f;
	void CustomTickFunction();

	float Damage;

public:	

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		// declare overlap end function
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
	
	void SetDamage(float ReceiveDamage);

	void DoDamage();

};
