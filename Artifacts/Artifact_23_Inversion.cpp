// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_23_Inversion.h"
#include "../All_Enemies/EnemyClass.h"
// killfeddback container
#include "../DataContainer/data_killfeedbackinfo.h"

// Sets default values
AArtifact_23_Inversion::AArtifact_23_Inversion() {
 	
	ThisArtifactType = EArtifactType::EKillFeedBack;
}

UData_KillFeedBackInfo* AArtifact_23_Inversion::ApplyKillFeedBackEffect(class UData_KillFeedBackInfo* KillInfo, AActor* Enemy) {
	if (IsValid(KillInfo)) {
		KillInfo->UpdateFrenzyReward(frenzyRatio);
		KillInfo->UpdateCalmReward(calmRatio);
	}
	
	return KillInfo;
}

void AArtifact_23_Inversion::UpdateFrenzyRatio(float newRatio) {
	frenzyRatio = newRatio;
}
void AArtifact_23_Inversion::UpdateCalmRatio(float newRatio) {
	calmRatio = newRatio;
}