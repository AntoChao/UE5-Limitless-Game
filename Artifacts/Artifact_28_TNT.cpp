// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_28_TNT.h"
#include "../All_Enemies/EnemyClass.h"
// killfeddback container
#include "../DataContainer/data_killfeedbackinfo.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AArtifact_28_TNT::AArtifact_28_TNT()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EKillFeedBack;
}

// Called when the game starts or when spawned
void AArtifact_28_TNT::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

UData_KillFeedBackInfo* AArtifact_28_TNT::ApplyKillFeedBackEffect(class UData_KillFeedBackInfo* KillInfo, AActor* Enemy)
{
	/* maybe getWorldDoesNotWork
	* may add main to ignore
	*/

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		ratioDamage,
		Enemy->GetActorLocation(),
		radius,
		nullptr,
		ignoredActors, 
		this,
		nullptr,
		false,
		ECollisionChannel::ECC_Visibility);

	return KillInfo;
}