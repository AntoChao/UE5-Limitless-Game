// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_GeneralClass.h"
#include "Weapon_AlienGun.generated.h"

UCLASS()
class TRUEPROJECT2_API AWeapon_AlienGun : public AWeapon_GeneralClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_AlienGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

};
