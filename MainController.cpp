// Fill out your copyright notice in the Description page of Project Settings.

#include "MainController.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "TrueGame2Instance.h"

AMainController::AMainController() {

}

void AMainController::BeginPlay() {
	Super::BeginPlay();
	
	// Add Input Mapping Context Original
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer())) {
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		SetupInputComponent();
	}

	MainCharacter = Cast<AMain>(GetPawn());
}

// Called to bind functionality to input
//void AMainController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
void AMainController::SetupInputComponent() {
	// Super::SetupPlayerInputComponent(PlayerInputComponent);
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		// Game Pause 
		EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Started, this, &AMainController::PauseGame);

		// Open Panel
		EnhancedInputComponent->BindAction(OpenPanelAction, ETriggerEvent::Started, this, &AMainController::OpenPanel);

		// Looking
		// Can not be replaced in all character class becuase of &AMain -> maybe use "this" / has to use self references
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainController::LookCTR);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainController::MoveCTR);

		// Running
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AMainController::RunCTR);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AMainController::RunEndCTR);

		// Jumpping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainController::JumpCTR);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMainController::StopJumpingCTR);

		// Dashing
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &AMainController::DashCTR);

		// Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AMainController::CrouchStartCTR);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AMainController::CrouchEndCTR);

		// Use Calm
		EnhancedInputComponent->BindAction(SpendCalmAction, ETriggerEvent::Started, this, &AMainController::SpendAllCalmCTR);

		//Change, the input should be part of ability and not for standard character
		// Passive
		EnhancedInputComponent->BindAction(PassiveAction, ETriggerEvent::Triggered, this, &AMainController::UsePassiveCTR);

		// Basic Attack
		EnhancedInputComponent->BindAction(BasicAttackAction, ETriggerEvent::Started, this, &AMainController::UseBasicAttackCTR);

		// Abilities
		EnhancedInputComponent->BindAction(AbilityActionOne, ETriggerEvent::Started, this, &AMainController::UseAbilityOneCTR);

		EnhancedInputComponent->BindAction(AbilityActionTwo, ETriggerEvent::Started, this, &AMainController::UseAbilityTwoCTR);

		EnhancedInputComponent->BindAction(AbilityActionThree, ETriggerEvent::Started, this, &AMainController::UseAbilityThreeCTR);

		EnhancedInputComponent->BindAction(AbilityActionFour, ETriggerEvent::Started, this, &AMainController::UseAbilityFourCTR);
	}
}

void AMainController::LookCTR(const FInputActionValue& Value) {
	if (IsValid(MainCharacter)) {
		MainCharacter->Look(Value);
	}
}

void AMainController::MoveCTR(const FInputActionValue& Value) {
	if (IsValid(MainCharacter)) {
		MainCharacter->Move(Value);
	}
}

void AMainController::RunCTR() {
	if (IsValid(MainCharacter)) {
		MainCharacter->Run();
	}
}

void AMainController::RunEndCTR() {
	if (IsValid(MainCharacter)) {
		MainCharacter->RunEnd();
	}
}

void AMainController::JumpCTR() {
	JumpCounter = JumpCounter + 1;
	if (AbleToJump) {
		if (JumpCounter % 2 != 0) {
			if (IsValid(MainCharacter)) {
				MainCharacter->Jump();
			}
		}
	}
}

void AMainController::StopJumpingCTR() {
	StopJumpCounter = StopJumpCounter + 1;
	if (StopJumpCounter % 2 != 0) {
		if (IsValid(MainCharacter)) {
			MainCharacter->StopJumping();
			AbleToJump = false;

			GetWorldTimerManager().SetTimer(ResetJumpTimer, this,
				&AMainController::ResetJump, JumpBreakTime, false);
		}
	}
}

void AMainController::ResetJump() {
	AbleToJump = true;
}

void AMainController::DashCTR() {
	DashCounter = DashCounter + 1;
	if (DashCounter % 2 != 0) {
		if (IsValid(MainCharacter)) {
			MainCharacter->Dash();
		}
	}
}

void AMainController::CrouchStartCTR() {
	if (IsValid(MainCharacter)) {
		MainCharacter->CrouchStart();
	}
}

void AMainController::CrouchEndCTR() {
	if (IsValid(MainCharacter)) {
		MainCharacter->CrouchEnd();
	}
}

void AMainController::SpendAllCalmCTR() {
	if (IsValid(MainCharacter)) {
		MainCharacter->SpendAllCalm();
	}
}

void AMainController::UsePassiveCTR() {
	if (IsValid(MainCharacter)) {
		MainCharacter->UsePassive();
	}
}

void AMainController::UseBasicAttackCTR() {
	if (IsValid(MainCharacter)) {
		MainCharacter->UseBasicAttack();
	}
}

void AMainController::UseAbilityOneCTR() {
	if (IsValid(MainCharacter)) {
		MainCharacter->UseAbilityOne();
	}
}

void AMainController::UseAbilityTwoCTR() {
	if (IsValid(MainCharacter)) {
		MainCharacter->UseAbilityTwo();
	}
}

void AMainController::UseAbilityThreeCTR() {
	if (IsValid(MainCharacter)) {
		MainCharacter->UseAbilityThree();
	}
}

void AMainController::UseAbilityFourCTR() {
	if (IsValid(MainCharacter)) {
		MainCharacter->UseAbilityFour();
	}
}