// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SceneComponent.h"

#include "../AllCharactersClass.h"
#include "../MainController.h"
#include "Components/WidgetComponent.h"
#include "../WidgetsBase/HitFloatingHealthUMG.h"
#include "../WidgetsBase/HealthBarUMG.h"
#include "../WidgetsBase/FloatingNumberActor.h"
#include "../WidgetsBase/HealthBarActor.h"
#include "../Decals/GeneralDecalActor.h"
#include "../Common_Enums.h"

#include "EnemyClass.generated.h"

/* Types
0 -> human
1 -> robot 
2 -> animal
3 ->..
*/


UCLASS()
class TRUEPROJECT2_API AEnemyClass : public AAllCharactersClass
{
	// Primate seccion
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyClass();

protected:
	virtual void Tick(float DeltaTime) override;

	/** Sphere collision component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyCollision")
		class UBoxComponent* CollisionComp;

	// MainBody
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class USkeletalMeshComponent* Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
		USceneComponent* HealthBarRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main To Target")
		class AMain* MainPlayerTarget;

	// HealthBar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
		TSubclassOf<class AHealthBarActor> HealthBarActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
		class AHealthBarActor* HealthBar;

	UFUNCTION(BlueprintCallable, Category = "Health Bar")
		void SpawnAttachHealthBar();

	UFUNCTION(BlueprintCallable, Category = "Display")
		void UpdateHealthBarDisplay();

	UFUNCTION(BlueprintCallable, Category = "Display")
		void RemoveHealthBar();


	// Health Bar visibility
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Visibility")
		FTimerHandle HealthBarVisibleTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Visibility")
		float HealthBarVisibleDuration = 5.0f;

	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		EEnemyRarity ItsRarity;

	/*
	Parameters: all parameters bools for blackboard should not be part of the enemyclass, should has a function that call activating for the aiEnemyClassController
	Tasks: Are individual tasks object that run in the blackboard, and if they do not fail, call enemy function. So each task should correspond at least one function
	*/

	// this is the ai controller that responde the enemy
	// enemy should call its parameters changes when something happend
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AAIEnemyClassController* EnemyController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FHitResult EnemyHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAIPerceptionStimuliSourceComponent* stimulus;
	
	void setup_stimulus();

	// Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float EnemyBaseDamage;

	// Take damage
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void ExtraDiedAction();
	
	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		void TakeDamageReaction(float Damage, AActor* DamageCauser);

	// Print the damage number
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		TSubclassOf<class AFloatingNumberActor> FloatingNumberActorClass;

	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		void SpawnFloatingHealthWidget(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		EDamageColor GetFloatHealthColor(float Damage);

	// save the damage amount
	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		void SaveTotalDamageAmount(float Damage);

	// select the closeast hit effect
	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		FTransform SelectHitEffectTrans(FVector DamageDauserPosition);
	
	// spawn niagara takedamage effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		class UNiagaraSystem* HitEffectNiagara;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		TArray<FName> HitEffectSocketsNames = { FName("Socket_HitEffectOne") , FName("Socket_HitEffectTwo"),
										FName("Socket_HitEffectThree"), FName("Socket_HitEffectFour"),
										FName("Socket_HitEffectFive"), FName("Socket_HitEffectSix") };

	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		void SpawnHitEffectNiagara(FTransform SpawnTrans);

	// spawn decal takedamage effect
	/* Spawn a few linetrace base on takedamage fhitresult, choose the closest one and spawn decal actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		TSubclassOf<class AGeneralDecalActor> HitEffectDecalClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		int TraceAmount = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		int TraceAngle = 10.0f;
	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		FTransform GetHitEffectDecalTrans(FVector DamageDauserPosition);

	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		void SpawnHitEffectDecal(FTransform SpawnTrans);

	// rewards
	class UData_KillFeedBackInfo* KillReward;
	
	UPROPERTY(EditAnywhere, Category = "ArtifactToSpawn")
		TSubclassOf<class AMiniWorld> AMiniWorldArtifact;

	UPROPERTY(EditAnywhere, Category = "ArtifactToSpawn")
		class AMiniWorld* ArtifactLoot;

	// fvector to calculate the attack position
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MainPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector SelfPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AttackDirection;
	
	// for random location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float GeneralDistance = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats NO Need To Set")
		float MinimalDistance;
	UFUNCTION(BlueprintCallable)
		void CalculateMinimalDistance();
	// the distance to determinate if it able to attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float BasicAttackDistance = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float AbilityOneDistance = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float AbilityTwoDistance = 1000.0f;;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float AbilityThreeDistance = 1000.0f;;

	// Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float PlayRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_BasicAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_Ability1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_Ability2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_Ability3;
	
	// All sounds and niagara should be part of animation

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void CustomTickFunction() override;

public:	

	// Health Bar Visibility
	UFUNCTION(BlueprintCallable, Category = "Health Bar Visibility")
		void SetHealthBarVisible();

	UFUNCTION(BlueprintCallable, Category = "Health Bar Visibility")
		void SetHealthBarNotVisible();

	UFUNCTION(BlueprintCallable)
		void SetRarity(EEnemyRarity ARarity);
	UFUNCTION()
		EEnemyRarity GetRarity();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float EnemyMovementSpeed = 300.0f;
	UFUNCTION(BlueprintCallable)
		void SetEnemyDefaultSpeed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LimitHeight;

	void SetHeightLimit();

	// ai controller stuff
	// 
	
	
	/* AI Behavior
	3 types:
		melee -> just chase main
		tactic -> random location -> try to shot -> reposition -> random location
			(SHOULD MOVE FAST)
		surrond -> get close to main but always in distance shotting
				-> like "chasing" in distance
	*/
	// Random location nearby main and self
	// BUT IT SHOULD BE RESET AFTER X SEGS
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		float GetGeneralDistance();

	// AI Position Control
	// The Pre posicion in order to Attack
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		virtual FVector GetPreAttackPosition();

	// some enemies have dash, this calculate the dash position
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		virtual FVector GetAttackFinishedPosition();

	UFUNCTION(BlueprintCallable, Category = "AI Control")
		virtual FVector GetPostAttackReposition();

	// Random Location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		class UNavigationSystemV1* NavArea;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		FVector RandomLocation;

	// based on a point and distance, generate a random location around main player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		int MaxRandomTryTimes = 100; /*only try 100 times*/
	
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		FVector GetRandLocation(FVector InitLocation, FVector TargetLocation, 
			float Distance);
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		void GenerateRandomPoint(FVector InitLocation, FVector TargetPosition);
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool RandomLocationValid(FVector TargetLocation, float MaxDistance);

	// Some function to calculate specific location
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		FVector EnemyGetRandMainLocation(); /*An safe escape location in case of error*/

	UFUNCTION(BlueprintCallable, Category = "AI Control")
		FVector GetRetreatLocation(FVector InitLocation, FVector TargetLocation,
			float RetreatDistance);
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		FVector GetOppositeLocation(FVector InitLocation, FVector TargetLocation,
			float OppositeDistance);

	// a bool that mean the enemy is using ability
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetIsUsingAbility1();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetIsUsingAbility2();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetIsUsingAbility3();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetIsAttacking();

	// Tie Breaker between abilities
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		int AmountOfPerformance; /*2, 3 or 4, depends on how many abilities does enemies has*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		bool PerformBasicAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		bool PerformAbilityOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		bool PerformAbilityTwo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		bool PerformAbilityThree;
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool IsPerformingAction();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetPerformBasicAttack();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetPerformAbilityOne();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetPerformAbilityTwo();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetPerformAbilityThree();

	UFUNCTION(BlueprintCallable, Category = "AI Control")
		void TieBreakAction();

	UFUNCTION(BlueprintCallable, Category = "AI BasicAttack")
		virtual bool IsAbleToUseBasicAttack();
	UFUNCTION(BlueprintCallable, Category = "AI Ability One")
		virtual bool IsAbleToUseAbility1();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Two")
		virtual bool IsAbleToUseAbility2();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Three")
		virtual bool IsAbleToUseAbility3();

	// Basic Attack
	// The attack do not deal any damage, it is just a collision box a timer 
	// basic attack is just a animation which fire a notifier which call function 
	// to deal damage to overlapped actors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI BasicAttack")
		bool IsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI BasicAttack")
		FTimerHandle BasicAttackTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI BasicAttack")
		float BasicAttackDuration; // the animation montage duration
	// Prepare -> show necesaries indicator for the action
	UFUNCTION(BlueprintCallable, Category = "AI BasicAttack")
		virtual void PrepareBasicAttack();
	UFUNCTION(BlueprintCallable, Category = "AI BasicAttack")
		virtual void BasicAttack();
	UFUNCTION(BlueprintCallable, Category = "AI BasicAttack")
		virtual void BasicAttackFinished();
	

	// Ability 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability One")
		FTimerHandle Ability1UsageTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability One")
		bool IsUsingAbility1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability One")
		float Ability1Duration;
	
	UFUNCTION(BlueprintCallable, Category = "AI Ability One")
		virtual void PrepareAbility1();
	UFUNCTION(BlueprintCallable, Category = "AI Ability One")
		virtual void Ability1();
	UFUNCTION(BlueprintCallable, Category = "AI Ability One")
		virtual void Ability1Finished();

	// Ability 2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Two")
		FTimerHandle Ability2UsageTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Two")
		bool IsUsingAbility2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Two")
		float Ability2Duration;
	
	UFUNCTION(BlueprintCallable, Category = "AI Ability Two")
		virtual void PrepareAbility2();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Two")
		virtual void Ability2();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Two")
		virtual void Ability2Finished();
	
	// Ability 3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Three")
		FTimerHandle Ability3UsageTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Three")
		bool IsUsingAbility3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Three")
		float Ability3Duration;

	UFUNCTION(BlueprintCallable, Category = "AI Ability Three")
		virtual void PrepareAbility3();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Three")
		virtual void Ability3();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Three")
		virtual void Ability3Finished();

	// Deal Overlapped Damage Function
	UPROPERTY(EditAnywhere, Category = "Overlap")
		TSet<AActor*> OverlappedActors = {};

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		virtual void DealDamage2Overlapped();

	UFUNCTION(BlueprintCallable)
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void ApplyDamageToMain(float damage);

	// main and enemy positions
	UFUNCTION(BlueprintCallable)
		void UpdatePositions();

	// Extra position function
	UFUNCTION(BlueprintCallable)
		FVector GetRandomNearbyLocationOfPlayer(float Distance);

	// Animation
	UFUNCTION(BlueprintCallable, Category = "Animation")
		virtual void PlayAnimBasicAttack();
	UFUNCTION(BlueprintCallable, Category = "Animation")
		virtual void PlayAnimAbilityOne();
	UFUNCTION(BlueprintCallable, Category = "Animation")
		virtual void PlayAnimAbilityTwo();
	UFUNCTION(BlueprintCallable, Category = "Animation")
		virtual void PlayAnimAbilityThree();

	UFUNCTION()
		void OnMontageBasicAttackEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		void OnMontageOneEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		void OnMontageTwoEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		void OnMontageThreeEnded(UAnimMontage* Montage, bool bInterrupted);

	// reward is directly to main
	UFUNCTION()
	void RewardMainCharacter();
	
	UFUNCTION()
		void testing();

	// Special Movement Of Enemy
	UPROPERTY(EditAnywhere, Category = "Timeline")
		class UCurveVector* MoveCurveVector;
	UPROPERTY(EditAnywhere, Category = "Timeline")
		class UCurveFloat* MoveCurveFloat;
	FTimeline CustomMoveTimeline;
	UFUNCTION(BlueprintCallable)
		virtual void CustomMoveTo();
	UFUNCTION()
		virtual void CustomMoving(float Value);
};
