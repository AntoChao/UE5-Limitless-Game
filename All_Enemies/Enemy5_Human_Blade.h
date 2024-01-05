// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "../meshes/Weapon_Blade.h"
#include "Enemy5_Human_Blade.generated.h"

UCLASS()
class LIMITLESS_API AEnemy5_Human_Blade : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy5_Human_Blade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Basic Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Blade> Weapon_BladeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AWeapon_Blade* Weapon_Blade;

	UFUNCTION(BlueprintCallable)
		void SpawnBladeInHand();

	UFUNCTION(BlueprintCallable)
		void UpdateSocketsInfo();


	/*the Blade is attached in the left hand
	* and set the right hand in the position of Blade socket	*/ 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FName Enemy_LeftHand_Socket = FName("Socket_Enemy_LeftHand");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FName Weapon_RightHand_Socket = FName("Socket_Weapon_RightHand");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Control")
		FVector LeftHandPosition;

	// Basic Attack
	
	// Ability 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		FVector TPLocation;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
		void SpawnTPNiagara(FVector ALocation);

public:	
	// Called every frame
	virtual void CustomTickFunction() override;

	// Basic attack -> slash
	virtual void BasicAttack() override;

	// tp close to the main
	virtual void Ability1() override;
};
