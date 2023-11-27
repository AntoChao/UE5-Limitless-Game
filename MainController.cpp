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
#include "Main.h"

AMainController::AMainController()
{

}

void AMainController::BeginPlay()
{
	Super::BeginPlay();
	
	// Add Input Mapping Context Original
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		SetupInputComponent();
	}
}

// Called to bind functionality to input
//void AMainController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
void AMainController::SetupInputComponent()
{
	// Super::SetupPlayerInputComponent(PlayerInputComponent);
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
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

void AMainController::LookCTR(const FInputActionValue& Value)
{
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->Look(Value);
	}
}

void AMainController::MoveCTR(const FInputActionValue& Value)
{
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->Move(Value);
	}
}

void AMainController::RunCTR()
{
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->Run();
	}
}

void AMainController::RunEndCTR()
{
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->RunEnd();
	}
}

void AMainController::JumpCTR()
{
	// Call the JumpAction function on the possessed character
	JumpCounter = JumpCounter + 1;
	if (JumpCounter % 2 != 0)
	{
		AMain* MainCharacter = Cast<AMain>(GetPawn());
		if (MainCharacter)
		{
			MainCharacter->Jump();
		}
	}	
}

void AMainController::StopJumpingCTR()
{
	// Call the JumpAction function on the possessed character
	StopJumpCounter = StopJumpCounter + 1;
	if (StopJumpCounter % 2 != 0)
	{
		AMain* MainCharacter = Cast<AMain>(GetPawn());
		if (MainCharacter)
		{
			MainCharacter->StopJumping();
		}
	}
	
}

void AMainController::DashCTR()
{
	// Call the JumpAction function on the possessed character
	DashCounter = DashCounter + 1;
	if (DashCounter % 2 != 0)
	{
		AMain* MainCharacter = Cast<AMain>(GetPawn());
		if (MainCharacter)
		{
			MainCharacter->Dash();
		}
	}
}

void AMainController::CrouchStartCTR()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Yellow, TEXT("Control to Crouch"));

	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->CrouchStart();
	}
}

void AMainController::CrouchEndCTR()
{
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->CrouchEnd();
	}
}

void AMainController::SpendAllCalmCTR()
{
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->SpendAllCalm();
	}
}

void AMainController::UsePassiveCTR()
{
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->UsePassive();
	}
}

void AMainController::UseBasicAttackCTR()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("USING BASIC ATTACK"));
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->UseBasicAttack();
	}
}

void AMainController::UseAbilityOneCTR()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("USING ABILITY ONE"));
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->UseAbilityOne();
	}
}

void AMainController::UseAbilityTwoCTR()
{
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->UseAbilityTwo();
	}
}

void AMainController::UseAbilityThreeCTR()
{
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->UseAbilityThree();
	}
}

void AMainController::UseAbilityFourCTR()
{
	// Call the JumpAction function on the possessed character
	AMain* MainCharacter = Cast<AMain>(GetPawn());
	if (MainCharacter)
	{
		MainCharacter->UseAbilityFour();
	}
}