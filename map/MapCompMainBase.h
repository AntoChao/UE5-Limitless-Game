// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common_Enums.h"
#include "GeneralMapComponent.h"
#include "MapCompMainBase.generated.h"

UCLASS()
class LIMITLESS_API AMapCompMainBase : public AGeneralMapComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapCompMainBase();

	UFUNCTION(BlueprintCallable, Category = "Activation")
		bool GetIfIsActivated();

	UFUNCTION(BlueprintCallable, Category = "Activation")
		void SetIfIsActivated(bool newActivation);

	UFUNCTION(BlueprintCallable, Category = "SpawnLocation")
		FVector GetSpawnMainOffSet();

protected:
	virtual void PlayerInAreaResponse(AMain* player) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation")
		bool IsActivated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnLocation")
		FVector SpawnMainOffSet = FVector(-460.0f, 320.0f, 80.0f);
};
