// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCompVoid.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "../Main.h"

// Sets default values
AMapCompVoid::AMapCompVoid() {

	return;
}

void AMapCompVoid::PlayerInAreaResponse(AMain* player) {

	if (IsValid(player)) {
		player->GameOverStepedVoid();
	}
}
