// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_GeneralClass.h"
#include "Weapon_Shotgun.generated.h"

UCLASS()
class LIMITLESS_API AWeapon_Shotgun : public AWeapon_GeneralClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Shotgun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

};
