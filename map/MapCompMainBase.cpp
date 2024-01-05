// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCompMainBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "../TrueProject2GameModeBase.h"
#include "../Main.h"

// Sets default values
AMapCompMainBase::AMapCompMainBase() {

	return;
}

void AMapCompMainBase::PlayerInAreaResponse(AMain* player) {
	if (IsValid(player)) {
		if (IsActivated) {
			ATrueProject2GameModeBase* GameMode = 
				Cast<ATrueProject2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			
			if (IsValid(GameMode)) {
				GameMode->SetGameOver(EGameOverReason::EFalseEnding);
			}
		}
	}
}

bool AMapCompMainBase::GetIfIsActivated() {
	return IsActivated;
}

void AMapCompMainBase::SetIfIsActivated(bool newActivation) {
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("ACTIVATE MAIN BASE"));
	IsActivated = newActivation;
}

FVector AMapCompMainBase::GetSpawnMainOffSet() {
	return SpawnMainOffSet;
}