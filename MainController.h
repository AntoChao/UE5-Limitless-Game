// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Main.h"
#include "MainController.generated.h"

/**
 *
 */
UCLASS()
class LIMITLESS_API AMainController : public APlayerController
{
	GENERATED_BODY()

protected:
	AMainController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		AMain* MainCharacter = nullptr;
	// Game Escape Pause
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PauseGameAction;
	
	// Open Panel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* OpenPanelAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;
	// RunningAction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* RunAction;
	// JumpAction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		int JumpCounter = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		int StopJumpCounter = 0;

	FTimerHandle ResetJumpTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		bool AbleToJump = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		float JumpBreakTime = 0.5f;

	UFUNCTION()
		void ResetJump();
	
	

	// DashAction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* DashAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		int DashCounter = 0;

	// Crouch Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* CrouchAction;
	// Use Calm Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* SpendCalmAction;
	// Passive
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PassiveAction;
	// Basic Attack / Accept Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* BasicAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		int BasicAttackCount = 0;

	// Abilities input
	//Maybe should be part of ability, like weapon. But in that way, the ability does not know which action is 1/2/3/4???
	//In that way, all abilities should be settle, each one correspond to 1/2/3/4
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AbilityActionOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		int AbilityOneCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AbilityActionTwo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		int AbilityTwoCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AbilityActionThree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		int AbilityThreeCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AbilityActionFour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		int AbilityFourCount = 0;

	// Game Pause
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Control")
		void PauseGame();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Control")
		void OpenPanel();

	// Looking
	UFUNCTION(BlueprintCallable, Category = "Control")
		void LookCTR(const FInputActionValue& Value);
	// Movement
	UFUNCTION(BlueprintCallable, Category = "Control")
		void MoveCTR(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "Control")
		void RunCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void RunEndCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void JumpCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void StopJumpingCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void DashCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void CrouchStartCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void CrouchEndCTR();
	// Abilities stuff
	UFUNCTION(BlueprintCallable, Category = "Control")
		void SpendAllCalmCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void UsePassiveCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void UseBasicAttackCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void UseAbilityOneCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void UseAbilityTwoCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void UseAbilityThreeCTR();
	UFUNCTION(BlueprintCallable, Category = "Control")
		void UseAbilityFourCTR();

public:

	// Called to bind functionality to input
	// void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	virtual void SetupInputComponent() override;
};