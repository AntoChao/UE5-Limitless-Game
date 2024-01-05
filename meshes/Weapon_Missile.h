// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_GProjectileClass.h"
#include "Weapon_Missile.generated.h"

UCLASS()
class LIMITLESS_API AWeapon_Missile : public AWeapon_GProjectileClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Missile();

protected:
	UPROPERTY(EditAnywhere)
		class AMain* Main;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		class USplineComponent* StartFireSpline1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		class USplineComponent* StartFireSpline2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		class USplineComponent* ReCalculateSpline1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		class USplineComponent* ReCalculateSpline2;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void MissileDieEffect();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void DoDamage(AActor* Actor) override;

	float ExplotionRadius = 300.0f;

	virtual void DieEffect() override;

public:	

	UFUNCTION(BlueprintCallable)
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);


};
