// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_20_Teeth.h"
#include "../All_Enemies/EnemyClass.h"
// killfeddback container
#include "../DataContainer/data_killfeedbackinfo.h"

// Sets default values
AArtifact_20_Teeth::AArtifact_20_Teeth() {
 	
	ThisArtifactType = EArtifactType::EKillFeedBack;
}

UData_KillFeedBackInfo* AArtifact_20_Teeth::ApplyKillFeedBackEffect(class UData_KillFeedBackInfo* KillInfo, AActor* Enemy)
{
	KillInfo->UpdateFrenzyReward(frenzyRatio);
	KillInfo->UpdateCalmReward(calmRatio);

	return KillInfo;
}

void AArtifact_20_Teeth::UpdateFrenzyRatio(float newRatio) {
	frenzyRatio = newRatio;
}
void AArtifact_20_Teeth::UpdateCalmRatio(float newRatio) {
	calmRatio = newRatio;
}