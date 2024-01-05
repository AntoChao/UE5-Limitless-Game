// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Common_Enums.h"
#include "GeneralMapComponent.generated.h"

UCLASS()
class LIMITLESS_API AGeneralMapComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralMapComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* BuildingBody;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Check if player is in building area
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		bool playerInArea = false;

	UFUNCTION(BlueprintCallable, Category = "Player")
		void SetPlayerInArea(bool isInArea);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area")
		EFloorType floorType = EFloorType::EConcrete;

	// Random Rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Rotation")
		bool setRandomLocation = false; /*a variable to be changed in blueprint*/
	UFUNCTION(BlueprintCallable, Category = "Random Rotation")
		void SetRandomRotation();

	// consequences when player get in to the area
	UFUNCTION(BlueprintCallable, Category = "Building Area overlap")
		virtual void PlayerInAreaResponse(AMain* player);
	UFUNCTION(BlueprintCallable, Category = "Building Area overlap")
		virtual void PlayerLeaveAreaResponse(AMain* player);

public:	
	UFUNCTION(BlueprintCallable, Category = "Building Area overlap")
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
