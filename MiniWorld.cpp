// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniWorld.h"
#include "Math/UnrealMathUtility.h" // idk if is this file
#include "All_Enemies/EnemyClass.h"
#include "Artifacts/GeneralArtifact.h"

//all artifacts
#include "Artifacts/Artifact_1_Blade.h"
#include "Artifacts/Artifact_2_SaoBlade.h"
#include "Artifacts/Artifact_3_Card.h"
#include "Artifacts/Artifact_4_BoxingGlove.h"
#include "Artifacts/Artifact_5_Punch.h"
#include "Artifacts/Artifact_6_SniperRifle.h"
#include "Artifacts/Artifact_7_Syringe.h"
#include "Artifacts/Artifact_8_Picture.h"
#include "Artifacts/Artifact_9_TinasDoggy.h"
#include "Artifacts/Artifact_10_Dumbbell.h"
#include "Artifacts/Artifact_11_Dice.h"
#include "Artifacts/Artifact_12_pumpkin.h"
#include "Artifacts/Artifact_13_Bandana.h"
#include "Artifacts/Artifact_14_Horseshoe.h"
#include "Artifacts/Artifact_15_Book.h"
#include "Artifacts/Artifact_16_Wingshoes.h"
#include "Artifacts/Artifact_17_Cloak.h"
#include "Artifacts/Artifact_18_SmokeGrenade.h"
#include "Artifacts/Artifact_19_Dinner.h"
#include "Artifacts/Artifact_20_Teeth.h"
#include "Artifacts/Artifact_21_Bomb.h"
#include "Artifacts/Artifact_22_Headphone.h"
#include "Artifacts/Artifact_23_inversion.h"
#include "Artifacts/Artifact_24_coin.h"
#include "Artifacts/Artifact_25_Tag.h"
#include "Artifacts/Artifact_26_Axe.h"
#include "Artifacts/Artifact_27_Instinct.h"
#include "Artifacts/Artifact_28_TNT.h"
#include "Artifacts/Artifact_29_Rune.h"
#include "Artifacts/Artifact_30_Heart.h"
#include "Artifacts/Artifact_31_Smelting.h"
#include "Artifacts/Artifact_32_Medkit.h"
#include "Artifacts/Artifact_33_Contract.h"
#include "Artifacts/Artifact_34_Caffeine.h"
#include "Artifacts/Artifact_35_Wings.h"
#include "Artifacts/Artifact_36_Cigaratte.h"
#include "Artifacts/Artifact_37_Drugs.h"
#include "Artifacts/Artifact_38_Totem.h"
#include "Artifacts/Artifact_39_Whip.h"
#include "Artifacts/Artifact_40_Fugu.h"

// Sets default values
AMiniWorld::AMiniWorld() {
 	
}

// Called when the game starts or when spawned
void AMiniWorld::BeginPlay() {
	Super::BeginPlay();
	
}

void AMiniWorld::SpawnArtifact(EEnemyRarity EnemyRarity, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation) {
	// Probability of spawning or not artifact
	int spawnArtifactChance = FMath::RandRange(1, 100);

	if (spawnArtifactChance >= spawnChance) {
		EArtifactRarity ArtifactRarity = GetRarityToSpawn(EnemyRarity);
		SpawnArtifactBasedRarity(ArtifactRarity, World, EnemyLocation, EnemyRotation);
	}
}

EArtifactRarity AMiniWorld::GetRarityToSpawn(EEnemyRarity Rarity) {
	// for now, it just random spwan, all artifacts should have rarity
	int Chance = FMath::RandRange(1, 100);
	EArtifactRarity CurrentArtifactRarity = EArtifactRarity::EUnknown;
	switch (Rarity) {
		case EEnemyRarity::ENormal: {
			/*
			* 85% -> normal artifact
			* 10% -> special artifact
			* 5% -> rare artifact
			* 0% -> OP artifact
			*/
			if (Chance < 85) {
				CurrentArtifactRarity = EArtifactRarity::ENormal;
			}
			else {
				if (Chance < 95) {
					CurrentArtifactRarity = EArtifactRarity::ESpecial;
				}
				else {
					CurrentArtifactRarity = EArtifactRarity::ERare;
				}
			}
			break;
		}
		case EEnemyRarity::ESpecial: {
			/*
			* 40% -> normal artifact
			* 45% -> special artifact
			* 14% -> rare artifact
			* 1% -> OP artifact
			*/
			if (Chance < 40) {
				CurrentArtifactRarity = EArtifactRarity::ENormal;
			}
			else {
				if (Chance < 85) {
					CurrentArtifactRarity = EArtifactRarity::ESpecial;
				}
				else {
					if (Chance < 99) {
						CurrentArtifactRarity = EArtifactRarity::ERare;
					}
					else {
						CurrentArtifactRarity = EArtifactRarity::EOP;
					}
					
				}
			}
			break;
		}
		case EEnemyRarity::EElite: {
			/*
			* 15% -> normal artifact
			* 35% -> special artifact
			* 40% -> rare artifact
			* 10% -> OP artifact
			*/
			if (Chance < 15) {
				CurrentArtifactRarity = EArtifactRarity::ENormal;
			}
			else {
				if (Chance < 50) {
					CurrentArtifactRarity = EArtifactRarity::ESpecial;
				}
				else {
					if (Chance < 90) {
						CurrentArtifactRarity = EArtifactRarity::ERare;
					}
					else {
						CurrentArtifactRarity = EArtifactRarity::EOP;
					}

				}
			}
			break;
		}
		case EEnemyRarity::EBoss: {
			/*
			* 0% -> normal artifact
			* 10% -> special artifact
			* 65% -> rare artifact
			* 25% -> OP artifact
			*/
			if (Chance < 10) {
				CurrentArtifactRarity = EArtifactRarity::ESpecial;
			}
			else {
				if (Chance < 75) {
					CurrentArtifactRarity = EArtifactRarity::ERare;
				}
				else {
					CurrentArtifactRarity = EArtifactRarity::EOP;
				}
			}
			break;
		}
		case EEnemyRarity::EGigaBoss: {
			/*
			* 0% -> normal artifact
			* 5% -> special artifact
			* 30% -> rare artifact
			* 65% -> OP artifact
			*/
			if (Chance < 5) {
				CurrentArtifactRarity = EArtifactRarity::ESpecial;
			}
			else {
				if (Chance < 35) {
					CurrentArtifactRarity = EArtifactRarity::ERare;
				}
				else {
					CurrentArtifactRarity = EArtifactRarity::EOP;
				}
			}
			break;
		}
		case EEnemyRarity::EUnknown: {
			// do nothing, wrong
			break;
		}
		default: {
			// do nothing, wrong
			break;
		}
	}
	return CurrentArtifactRarity;
}

void AMiniWorld::SpawnArtifactBasedRarity(EArtifactRarity ArtifactRarity, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation) {
	switch (ArtifactRarity) {
		// for now, just random chances, should redo after defined
		case EArtifactRarity::ENormal: {
			int Chance = FMath::RandRange(1, normal); // need to know the max and min
			SpawnNormalArtifact(Chance, World, EnemyLocation, EnemyRotation);
			break;
		}
		case EArtifactRarity::ESpecial: {
			int Chance = FMath::RandRange(1, special);
			SpawnSpecialArtifact(Chance, World, EnemyLocation, EnemyRotation);
			break;
		}
		case EArtifactRarity::ERare: {
			int Chance = FMath::RandRange(1, rare);
			SpawnRareArtifact(Chance, World, EnemyLocation, EnemyRotation);
			break;
		}
		case EArtifactRarity::EOP: {
			int Chance = FMath::RandRange(1, op);
			SpawnOPArtifact(Chance, World, EnemyLocation, EnemyRotation);
			break;
		}
		case EArtifactRarity::EUnknown: {
			// do nothing
			break;
		}
		default: {
			// do nothing
			break;
		}
	}
}

void AMiniWorld::SpawnNormalArtifact(int Chance, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation) {
	switch (Chance) {
		case 1: {
			World->SpawnActor<AArtifact_1_Blade>(Artifact_1_Blade, EnemyLocation, EnemyRotation);
			break;
		}
		case 2:{
			World->SpawnActor<AArtifact_2_SaoBlade>(Artifact_2_SaoBlade, EnemyLocation, EnemyRotation);
			break;
		}
		case 3:{
			World->SpawnActor<AArtifact_3_Card>(Artifact_3_Card, EnemyLocation, EnemyRotation);
			break;
		}
		case 4:{
			World->SpawnActor<AArtifact_4_BoxingGlove>(Artifact_4_BoxingGlove, EnemyLocation, EnemyRotation);
			break;
		}
		case 5:{
			World->SpawnActor<AArtifact_5_Punch>(Artifact_5_Punch, EnemyLocation, EnemyRotation);
			break;
		}
		case 6:{
			World->SpawnActor<AArtifact_6_SniperRifle>(Artifact_6_SniperRifle, EnemyLocation, EnemyRotation);
			break;
		}
		case 7:{
			World->SpawnActor<AArtifact_9_TinasDoggy>(Artifact_9_TinasDoggy, EnemyLocation, EnemyRotation);
			break;
		}
		case 8:{
			World->SpawnActor<AArtifact_13_Bandana>(Artifact_13_Bandana, EnemyLocation, EnemyRotation);
			break;
		}
		case 9:{
			World->SpawnActor<AArtifact_14_Horseshoe>(Artifact_14_Horseshoe, EnemyLocation, EnemyRotation);
			break;
		}
		case 10:{
			World->SpawnActor<AArtifact_16_Wingshoes>(Artifact_16_Wingshoes, EnemyLocation, EnemyRotation);
			break;
		}
		case 11:{
			World->SpawnActor<AArtifact_18_SmokeGrenade>(Artifact_18_SmokeGrenade, EnemyLocation, EnemyRotation);
			break;
		}
		case 12:{
			World->SpawnActor<AArtifact_23_Inversion>(Artifact_23_Inversion, EnemyLocation, EnemyRotation);
			break;
		}
		case 13:{
			World->SpawnActor<AArtifact_24_Coin>(Artifact_24_Coin, EnemyLocation, EnemyRotation);
			break;
		}
		case 14:{
			World->SpawnActor<AArtifact_31_Smelting>(Artifact_31_Smelting, EnemyLocation, EnemyRotation);
			break;
		}
		default:{
			break;
		}
	}
}

void AMiniWorld::SpawnSpecialArtifact(int Chance, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation){
	switch (Chance){
		case 1:{
			World->SpawnActor<AArtifact_7_Syringe>(Artifact_7_Syringe, EnemyLocation, EnemyRotation);
			break;
		}
		case 2:{
			World->SpawnActor<AArtifact_8_Picture>(Artifact_8_Picture, EnemyLocation, EnemyRotation);
			break;
		}
		case 3:{
			World->SpawnActor<AArtifact_10_Dumbbell>(Artifact_10_Dumbbell, EnemyLocation, EnemyRotation);
			break;
		}
		case 4:{
			World->SpawnActor<AArtifact_12_pumpkin>(Artifact_12_pumpkin, EnemyLocation, EnemyRotation);
			break;
		}
		case 5:{
			World->SpawnActor<AArtifact_15_Book>(Artifact_15_Book, EnemyLocation, EnemyRotation);
			break;
		}
		case 6:{
			World->SpawnActor<AArtifact_17_Cloak>(Artifact_17_Cloak, EnemyLocation, EnemyRotation);
			break;
		}
		case 7:{
			World->SpawnActor<AArtifact_19_Dinner>(Artifact_19_Dinner, EnemyLocation, EnemyRotation);
			break;
		}
		case 8:{
			World->SpawnActor<AArtifact_20_Teeth>(Artifact_20_Teeth, EnemyLocation, EnemyRotation);
			break;
		}
		case 9:{
			World->SpawnActor<AArtifact_21_Bomb>(Artifact_21_Bomb, EnemyLocation, EnemyRotation);
			break;
		}
		case 10:{
			World->SpawnActor<AArtifact_22_Headphone>(Artifact_22_Headphone, EnemyLocation, EnemyRotation);
			break;
		}
		case 11:{
			World->SpawnActor<AArtifact_25_Tag>(Artifact_25_Tag, EnemyLocation, EnemyRotation);
			break;
		}
		case 12:{
			World->SpawnActor<AArtifact_26_Axe>(Artifact_26_Axe, EnemyLocation, EnemyRotation);
			break;
		}
		case 13:{
			World->SpawnActor<AArtifact_27_Instinct>(Artifact_27_Instinct, EnemyLocation, EnemyRotation);
			break;
		}
		case 14:{
			World->SpawnActor<AArtifact_29_Rune>(Artifact_29_Rune, EnemyLocation, EnemyRotation);
			break;
		}
		case 15:{
			World->SpawnActor<AArtifact_37_Drugs>(Artifact_37_Drugs, EnemyLocation, EnemyRotation);
			break;
		}
		case 16:{
			World->SpawnActor<AArtifact_38_Totem>(Artifact_38_Totem, EnemyLocation, EnemyRotation);
			break;
		}
		default:{
			break;
		}
	}
}

void AMiniWorld::SpawnRareArtifact(int Chance, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation) {
	switch (Chance){
		case 1:{
			World->SpawnActor<AArtifact_11_Dice>(Artifact_11_Dice, EnemyLocation, EnemyRotation);
			break;
		}
		case 2:{
			World->SpawnActor<AArtifact_28_TNT>(Artifact_28_TNT, EnemyLocation, EnemyRotation);
			break;
		}
		case 3:{
			World->SpawnActor<AArtifact_30_Heart>(Artifact_30_Heart, EnemyLocation, EnemyRotation);
			break;
		}
		case 4:{
			World->SpawnActor<AArtifact_32_Medkit>(Artifact_32_Medkit, EnemyLocation, EnemyRotation);
			break;
		}
		case 5:{
			World->SpawnActor<AArtifact_33_Contract>(Artifact_33_Contract, EnemyLocation, EnemyRotation);
			break;
		}
		case 6:{
			World->SpawnActor<AArtifact_34_Caffeine>(Artifact_34_Caffeine, EnemyLocation, EnemyRotation);
			break;
		}
		case 7:{
			World->SpawnActor<AArtifact_36_Cigaratte>(Artifact_36_Cigaratte, EnemyLocation, EnemyRotation);
			break;
		}
		case 8:{
			World->SpawnActor<AArtifact_39_Whip>(Artifact_39_Whip, EnemyLocation, EnemyRotation);
			break;
		}
		case 9:{
			World->SpawnActor<AArtifact_40_Fugu>(Artifact_40_Fugu, EnemyLocation, EnemyRotation);
			break;
		}
		default:{
			break;
		}
	}
}
void AMiniWorld::SpawnOPArtifact(int Chance, UWorld* const World, FVector EnemyLocation, FRotator EnemyRotation) {
	switch (Chance) {
		case 1: {
			World->SpawnActor<AArtifact_35_Wings>(Artifact_35_Wings, EnemyLocation, EnemyRotation);
			break;
		}
		default: {
			break;
		}
	}
}
