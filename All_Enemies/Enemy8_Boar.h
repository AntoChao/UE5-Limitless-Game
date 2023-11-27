// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy8_Boar.generated.h"

UCLASS()
class TRUEPROJECT2_API AEnemy8_Boar : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy8_Boar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void CustomTickFunction() override;

	float FlySpeed;
	float DashSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		bool bFlyUp;

	//Basic Stats
	FHitResult EnemyHit;
	
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;

	
	// Ability 1 -> JumpMeleeAttack
	/*
	* 
	*/
	void Ability1Finished() override;

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


	// declare overlap end function
	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	
	// Ability 2 -> TripleMeleeAttack
	UPROPERTY(EditAnywhere, Category = "Ability")
		TSubclassOf<class AEnemy1_Bird_WindSlash> WindSlashClass;

	UPROPERTY(EditAnywhere, Category = "Ability")
		class AEnemy1_Bird_WindSlash* WindSlash1;
	
	FVector InitLocation1;
	FRotator InitRotation1 = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Ability")
		class AEnemy1_Bird_WindSlash* WindSlash2;

	FVector InitLocation2;
	FRotator InitRotation2 = FRotator(0.0f, 0.0f, 0.0f);

	void CalculateAbility2Stats();

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// Receive Damage
	//virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Ability1() override;
	virtual void Ability2() override;
	virtual bool IsAbleToUseAbility1() override;
	virtual bool IsAbleToUseAbility2() override;

};
