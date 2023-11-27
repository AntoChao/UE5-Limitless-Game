// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiniWorld.generated.h"

/*
* A actor that allow to spawn whatever people need:
* - Artifact
* - Ability stuff (IDK)
*/

UCLASS()
class TRUEPROJECT2_API AMiniWorld : public AActor
{
	GENERATED_BODY()

public:
	AMiniWorld();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	//SO, THERE IS THE CORRECT FORM TO DO IT -> CREATE 4 LIST PER RARITY AND FOR LOOP...
	
	// amount of artifacts per type
	UPROPERTY()
		int normal = 14;
	UPROPERTY()
		int special = 16;
	UPROPERTY()
		int rare = 9;
	UPROPERTY()
		int op = 1;

	// no instances -> just object class
	// Artifacts Section

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_1_Blade> Artifact_1_Blade;

	UPROPERTY(EditDefaultsOnly, Category = "AttackArtifact")
		TSubclassOf<class AArtifact_2_SaoBlade> Artifact_2_SaoBlade;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_3_Card> Artifact_3_Card;

	UPROPERTY(EditDefaultsOnly, Category = "AttackArtifact")
		TSubclassOf<class AArtifact_4_BoxingGlove> Artifact_4_BoxingGlove;

	UPROPERTY(EditDefaultsOnly, Category = "AttackArtifact")
		TSubclassOf<class AArtifact_5_Punch> Artifact_5_Punch;

	UPROPERTY(EditDefaultsOnly, Category = "AttackArtifact")
		TSubclassOf<class AArtifact_6_SniperRifle> Artifact_6_SniperRifle;

	UPROPERTY(EditDefaultsOnly, Category = "AttackArtifact")
		TSubclassOf<class AArtifact_7_Syringe> Artifact_7_Syringe;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_8_Picture> Artifact_8_Picture;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_9_TinasDoggy> Artifact_9_TinasDoggy;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_10_Dumbbell> Artifact_10_Dumbbell;

	UPROPERTY(EditDefaultsOnly, Category = "CostArtifact")
		TSubclassOf<class AArtifact_11_Dice> Artifact_11_Dice;

	UPROPERTY(EditDefaultsOnly, Category = "AttackArtifact")
		TSubclassOf<class AArtifact_12_pumpkin> Artifact_12_pumpkin;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_13_Bandana> Artifact_13_Bandana;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_14_Horseshoe> Artifact_14_Horseshoe;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_15_Book> Artifact_15_Book;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_16_Wingshoes> Artifact_16_Wingshoes;

	UPROPERTY(EditDefaultsOnly, Category = "DefenseArtifact")
		TSubclassOf<class AArtifact_17_Cloak> Artifact_17_Cloak;

	UPROPERTY(EditDefaultsOnly, Category = "DefenseArtifact")
		TSubclassOf<class AArtifact_18_SmokeGrenade> Artifact_18_SmokeGrenade;

	UPROPERTY(EditDefaultsOnly, Category = "KillFeedBackArtifact")
		TSubclassOf<class AArtifact_19_Dinner> Artifact_19_Dinner;

	UPROPERTY(EditDefaultsOnly, Category = "KillFeedBackArtifact")
		TSubclassOf<class AArtifact_20_Teeth> Artifact_20_Teeth;

	UPROPERTY(EditDefaultsOnly, Category = "AttackArtifact")
		TSubclassOf<class AArtifact_21_Bomb> Artifact_21_Bomb;
	
	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_22_Headphone> Artifact_22_Headphone;

	UPROPERTY(EditDefaultsOnly, Category = "KillFeedBackArtifact")
		TSubclassOf<class AArtifact_23_Inversion> Artifact_23_Inversion;

	UPROPERTY(EditDefaultsOnly, Category = "AttackArtifact")
		TSubclassOf<class AArtifact_24_Coin> Artifact_24_Coin;

	UPROPERTY(EditDefaultsOnly, Category = "AttackArtifact")
		TSubclassOf<class AArtifact_25_Tag> Artifact_25_Tag;

	UPROPERTY(EditDefaultsOnly, Category = "AttackArtifact")
		TSubclassOf<class AArtifact_26_Axe> Artifact_26_Axe;

	UPROPERTY(EditDefaultsOnly, Category = "DefenseArtifact")
		TSubclassOf<class AArtifact_27_Instinct> Artifact_27_Instinct;

	UPROPERTY(EditDefaultsOnly, Category = "KillFeedBackArtifact")
		TSubclassOf<class AArtifact_28_TNT> Artifact_28_TNT;
	
	UPROPERTY(EditDefaultsOnly, Category = "CostArtifact")
		TSubclassOf<class AArtifact_29_Rune> Artifact_29_Rune;

	UPROPERTY(EditDefaultsOnly, Category = "DiedArtifact")
		TSubclassOf<class AArtifact_30_Heart> Artifact_30_Heart;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_31_Smelting> Artifact_31_Smelting;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_32_Medkit> Artifact_32_Medkit;
	
	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_33_Contract> Artifact_33_Contract;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_34_Caffeine> Artifact_34_Caffeine;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_35_Wings> Artifact_35_Wings;

	UPROPERTY(EditDefaultsOnly, Category = "DefenseArtifact")
		TSubclassOf<class AArtifact_36_Cigaratte> Artifact_36_Cigaratte;

	UPROPERTY(EditDefaultsOnly, Category = "AttackArtifact")
		TSubclassOf<class AArtifact_37_Drugs> Artifact_37_Drugs;

	UPROPERTY(EditDefaultsOnly, Category = "SpecialArtifact")
		TSubclassOf<class AArtifact_38_Totem> Artifact_38_Totem;
	
	UPROPERTY(EditDefaultsOnly, Category = "DefenseArtifact")
		TSubclassOf<class AArtifact_39_Whip> Artifact_39_Whip;

	UPROPERTY(EditDefaultsOnly, Category = "PickUpArtifact")
		TSubclassOf<class AArtifact_40_Fugu> Artifact_40_Fugu;

public:
	UFUNCTION()
		void SpawnArtifact(EEnemyRarity Rarity, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation);

	UFUNCTION()
		EArtifactRarity GetRarityToSpawn(EEnemyRarity Rarity);

	UFUNCTION()
		void SpawnArtifactBasedRarity(EArtifactRarity ArtifactRarity, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation);

	UFUNCTION()
		void SpawnNormalArtifact(int Chance, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation);
	UFUNCTION()
		void SpawnSpecialArtifact(int Chance, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation);
	UFUNCTION()
		void SpawnRareArtifact(int Chance, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation);
	UFUNCTION()
		void SpawnOPArtifact(int Chance, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation);

};