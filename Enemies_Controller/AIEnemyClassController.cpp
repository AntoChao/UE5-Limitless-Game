// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyClassController.h"
// recognize the cahracter
#include "GameFramework/Character.h"
#include "../All_Enemies/EnemyClass.h"
#include "../Main.h"

// behavior tree
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

// perception
#include "Perception/PawnSensingComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"

// gameplay
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"



AAIEnemyClassController::AAIEnemyClassController() {
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
}

void AAIEnemyClassController::BeginPlay() {
	Super::BeginPlay();
	
	PawnSensing->OnSeePawn.AddUniqueDynamic(this, &AAIEnemyClassController::OnSeePawn);
	
	SenseMain = false;
	GotSpecialStatus = false;

	RunBehaviorTree(BehaviorTree);
}

bool AAIEnemyClassController::GetIsSensingPlayer() {
	return SenseMain;
}

void AAIEnemyClassController::IsTooCloseToMain(bool bClose) {
	GetBlackboardComponent()
		->SetValueAsBool(FName("Main Too Close"), bClose);
}

void AAIEnemyClassController::SetSpecialStatus(bool SpcialStatus) {
	if (SpcialStatus) {
		GetBlackboardComponent()
			->SetValueAsBool(FName("Got Special Status"), SpcialStatus);
	}
	else {
		GetBlackboardComponent()
			->SetValueAsBool(FName("Got Special Status"), SpcialStatus);
	}
}

void AAIEnemyClassController::OnSeePawn(APawn* PlayerPawn) {
	AMain* Player = Cast<AMain>(PlayerPawn);

	if (IsValid(Player)) {
		SetCanSeePlayer(true, Player);
		RunRetriggerableTimer();
	}
	else {
		SetCanSeePlayer(false, Player);
	}
}

void AAIEnemyClassController::SetCanSeePlayer(bool SeePlayer, UObject* Player) {
	if (SeePlayer) {

		SenseMain = SeePlayer;

		GetBlackboardComponent()
			->SetValueAsBool(FName("Can See Player"), SenseMain);

		GetBlackboardComponent()
			->SetValueAsObject(FName("Player Target"), Player);
	}
	else {
		SenseMain = SeePlayer;

		GetBlackboardComponent()
			->SetValueAsBool(FName("Can See Player"), SenseMain);
	}
}

void AAIEnemyClassController::RunRetriggerableTimer() {
	GetWorld()->GetTimerManager().ClearTimer(RetriggerableTimerHandle);

	FunctionDelegate.BindUFunction(this, FName("SetCanSeePlayer"),
		false, GetPawn());

	GetWorld()->GetTimerManager().SetTimer(RetriggerableTimerHandle,
		FunctionDelegate, PawnSensing->SensingInterval * 2.0f, false);
}

void AAIEnemyClassController::SetStatusCharm(bool GotCharm, class UObject* CharmActor) {
	if (GotCharm) {
		GetBlackboardComponent()
			->SetValueAsBool(FName("Got Status Charm"), GotCharm);

		GetBlackboardComponent()
			->SetValueAsObject(FName("Charm Target"), CharmActor);
	}
	else {
		GetBlackboardComponent()
			->SetValueAsBool(FName("Got Status Charm"), GotCharm);
	}
}