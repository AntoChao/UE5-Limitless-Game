// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_GeneralClass.h"
#include "Components/SplineComponent.h"
#include "Weapon_GProjectileClass.generated.h"

/* Animation and sound should be part of the weapon
* because the weapon is the one who fire and make sound...
*/
UCLASS()
class LIMITLESS_API AWeapon_GProjectileClass : public AWeapon_GeneralClass
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon_GProjectileClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	virtual void CustomTickFunction() override;

	//****************************************************************************************
	/* FLY WEAPON 
	VARIABLES AND FUNCTION EXPLANATION
	* Rootlocation = ROOT SHUOLD NEVER CHANGE
	* CollisionCompLocation = Root + DeltaTrans
	* DeltaTrans -> RlativeLocation/Rotation -> change every tick and spline 
	* TargetLocation -> MainTarget
	* AttackDirection = TargetLocation - CollisionComLocation ????
	* setActorLocation (ROOT LOCATION) -> NewLocation -> so the collision Comp move at the same time
	
	Explanation on what is going on: So basically SetRelativeLocation does not work properly
	by because it is a character and not a actor, it does not have a sceneRootComponent
	So the Parent RelativeLocation is 000, Need to manually add RootPosition.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector RootLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector CollisionLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform DeltaTrans;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector TargetLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AActor* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AttackDirection;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//class AActor* EnemyTarget;


	// need the specific weapons to add their splines in to the set
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		bool bStartingFire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		TArray<class USplineComponent*> StartSplines = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		class USplineComponent* StartSplineChosen;
	UFUNCTION(BlueprintCallable, Category = "Spline")
		virtual void StartFire(float DeltaTime);
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		bool bReCalculatingPath;
	// just for recalculate -> the distance of player and targetlocation when projectile get in place
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		float ReFireDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		int ReCalculateMaximum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		int ReCalculateCounter;
	UFUNCTION(BlueprintCallable, Category = "Spline")
		void ReCalculateTrigger();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		TArray<class USplineComponent*> ReCalculateSplines = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		class USplineComponent* ReCalculateSplineChosen;
	UFUNCTION(BlueprintCallable, Category = "Spline")
		virtual void ReCalculatePath(float DeltaTime);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bNormalFire;
	UFUNCTION(BlueprintCallable)
		virtual void NormalFire(float DeltaTime);
	// chaseParameter == True -> constantly update player location, else not
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool ChaseParameter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bGravityFire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector GravityForce = FVector(0.0f, 0.0f, 10.0f);
	UFUNCTION(BlueprintCallable)
		virtual void GravityFire(float DeltaTime);
	UFUNCTION(BlueprintCallable)
		virtual void CalculateGravityForce();

	// for projectiles that normal fire (no recalculation). Die when reach location
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ReachOffSet = 10.0f;
	UFUNCTION(BlueprintCallable)
		void IfReachLocation();

	// depend which type of fire is setted
	UFUNCTION(BlueprintCallable)
		virtual void ReachLocationEffect();

	UFUNCTION(BlueprintCallable)
		void StopMoving();

	// general parameter
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TravelSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		float SplineDistance;

	virtual void DoDamage(AActor* Actor) override;

public:

	/* *******************
	* There should be 2 types of fire -> auto or not
	* 1 -> does not recognize main, it only travel to location X and do something
	*	   BUT even it not recognize main, it could recalculate the path and do the stuff
	* 2 -> know main, so it updates main location each segs in order chase main
	*/
	UFUNCTION(BlueprintCallable)
		void SetbStartingFire(float ATravelSpeed, bool StartFireState);
	UFUNCTION(BlueprintCallable)
		void SetbReCalculatingPath(bool ReCalculateState);
	// Normal Fire could be -> auto/cahse on/off
	UFUNCTION(BlueprintCallable)
		void SetbNormalFire(float ATravelSpeed, bool FireState);
	UFUNCTION(BlueprintCallable)
		void SetbGravityFire(float ATravelSpeed, bool FireState);

	// in general, only be used for chase weapons
	UFUNCTION(BlueprintCallable)
		void UpdateLocationVariable();
	UFUNCTION(BlueprintCallable)
		void UpdateCollisionCompPosition();

	UFUNCTION(BlueprintCallable)
		void SetTarget(AActor* ATarget);
	UFUNCTION(BlueprintCallable)
		void SetTargetLocation(FVector ATargetLocation);

	UFUNCTION(BlueprintCallable)
		FVector GetCollisionLocation();
};
