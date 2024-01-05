// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common_Enums.h"
#include "GeneralMapComponent.h"
#include "MapCompSecretPortal.generated.h"

UCLASS()
class LIMITLESS_API AMapCompSecretPortal : public AGeneralMapComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapCompSecretPortal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation")
		bool IsActivated = false;

	UFUNCTION(BlueprintCallable, Category = "Activation")
		bool GetIfIsActivated();

	UFUNCTION(BlueprintCallable, Category = "Activation")
		void SetIfIsActivated(bool newActivation);

protected:
	virtual void PlayerInAreaResponse(AMain* player) override;
	
};
