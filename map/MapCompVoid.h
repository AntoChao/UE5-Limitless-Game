// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common_Enums.h"
#include "GeneralMapComponent.h"
#include "MapCompVoid.generated.h"

UCLASS()
class LIMITLESS_API AMapCompVoid : public AGeneralMapComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapCompVoid();

protected:
	virtual void PlayerInAreaResponse(AMain* player) override;

};
