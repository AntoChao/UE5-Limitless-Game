// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TrueGame2Instance.h"
#include "Common_Enums.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#include "TrueProject2GameModeBase.generated.h"

UCLASS()
class LIMITLESS_API ATrueProject2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance")
		UTrueGame2Instance* GameInstance;

	// Games Endinig

	// Ending Survive
	// if player survive xx minutes -> run a 30 segs timer -> finish
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		FTimerHandle ExploreTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		float ExploreSeg = 30.0f; /*30 segs*/
	UFUNCTION(BlueprintCallable, Category = "Game Over")
		void FinishExploration();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		int SurviveDay = 15; /*days*/
	UFUNCTION(BlueprintCallable, Category = "Game Over")
		void CheckSurvive();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		bool isSurvived = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		FTimerHandle SurvivedTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		float ExitSeg = 30.0f; /*30 segs*/
	UFUNCTION(BlueprintCallable, Category = "Game Over")
		void Survived();

	// Play Music
	UFUNCTION(BlueprintCallable, Category = "BGM")
		void PlayBGM();
	
	UFUNCTION(BlueprintCallable, Category = "BGM")
		void PlayChillBGM();
	UFUNCTION(BlueprintCallable, Category = "BGM")
		void PlayCombatBGM();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BGM")
		UAudioComponent* BGMComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BGM")
		USoundCue* ChillBGMSoundCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BGM")
		USoundCue* CombatBGMSoundCue;

	// Main Base
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Base")
		FVector MainBaseLocation = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Base")
		FRotator MainBaseRotation = FRotator(0.0f, 0.0f, 0.0f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Base")
		TSubclassOf<class AMapCompMainBase> MainBaseClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Base")
		AMapCompMainBase* MainBase;

	UFUNCTION(BlueprintCallable, Category = "Main Base")
		void SpawnMainBase();

	// Secret Portal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret Portal")
		FVector SecretPortalLocation = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret Portal")
		FRotator SecretPortalRotation = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret Portal")
		TSubclassOf<class AMapCompSecretPortal> SecretPortalClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret Portal")
		AMapCompSecretPortal* SecretPortal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret Portal")
		FTimerHandle SecretPortalTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Secret Portal")
		float SecretPortalSpawnSegs = 60.0f;
	UFUNCTION(BlueprintCallable, Category = "Secret Portal")
		void SpawnSecretPortal();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Secret Portal")
		void SecretPortalSpawnSound();

	// Open Game State
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "GameState")
		void OpenPreGameState();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "GameState")
		void OpenPlayingState();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "GameState")
		void OpenPostGameState();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Open Widget")
		void OpenInitMenuWidget();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Open Widget")
		void OpenPreGameWidget();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Open Widget")
		void OpenPostGameWidget();

	// Spawn Main Parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Main")
		float MainHalfHeight = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Main")
		FVector MainSpawnLocation = FVector(100.0f, 100.0f, 100.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Main")
		FRotator MainSpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	// Past PostGame Stats
	UFUNCTION(BlueprintCallable, Category = "Game State")
		void PastAllPostGameStats();

	// Time/ day control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		FTimerHandle RunTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		float CurrentSecond = 0.0f; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		float CurrentMinute = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		float CurrentHour = 6.0f;;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		float CurrentDay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		float SegRate = 2.4f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		float Seg2Minutes = 60.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		float Minutes2Hour = 60.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		float Hour2Day = 24.0f;

	// Morning and night control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		bool bIsInMorning = true; /*day or night*/

	// Night -> 0 am to 4 am, rest is morning
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		float nightStart = 4.0f;

	// Time/ Day
	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void TimeRunning();
	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void CheckTime();
	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void HandleTime();

	// Spawn Enemies Parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		float minRadio = 3000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		float maxRadio = 15000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		float spawnRate = 7.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		float minSpawnRate = 1.0f;

	// Modifiers for spwaning difficulty
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float difficultyBuff = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float difficultyModifier = 1.25f;

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void UpdateDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void BuffAllEnemiesByDifficulty();

	// Modifiers for spwaning day/ night
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float nightBuff = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float nightBuffModifier = 1.25f;

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void UpdateNightBuff();

	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void BuffAllNightEnemies();
	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void DebuffAllDayEnemies();

	// Player To Recognize
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		TSubclassOf<class AMain> MainClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		class AMain* MainCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		bool MainIsSpawned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		FVector PlayerLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		FRotator PlayerRotation;

	UFUNCTION(BlueprintCallable, Category = "Main")
		void SpawnMain();

	// Player UI -> as gamemode should also have its control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
		class UPlayerStatsUMG* PlayerHUD;

	// Objectives
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		FText CurrentObjective = FText::FromString("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		FText ObjExplore = FText::FromString("EXPLORE SURRONDING");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		FText ObjSurvive = FText::FromString("SURVIVE 15 DAYS");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		FText ObjPrepareExit = FText::FromString("WAIT 1 DAY FOR THE EXIT");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		FText ObjExit = FText::FromString("RETURN BASE TO EXIT");

	// Enemies To Recognize
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		float SpawnHeightOffset = 120.0f;

	// All Enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		TArray<AEnemyClass*> EnemiesSpawned = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		int enemyRarities = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		int normalEnemy = 7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		int specialEnemy = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		int eliteEnemy = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		int bossEnemy = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		int gigabossEnemy;


	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		AEnemyClass* GetRandomEnemy();
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		EEnemyRarity GenerateRandomEnemyRarity();
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		AEnemyClass* GenerateNormalEnemy();
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		AEnemyClass* GenerateSpecialEnemy();
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		AEnemyClass* GenerateEliteEnemy();
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		AEnemyClass* GenerateBossEnemy();

	// Normal Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy1_Bird> EnemyBirdClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy2_Parasite_Baby> EnemyParasiteBabyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy3_Parasite_Rookie> EnemyParasiteRookieClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy5_Human_Blade> EnemyHumanBladeClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy6_Human_Pistol> EnemyHumanPistolClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy7_Human_Shotgun> EnemyHumanShotgunClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy8_Boar> EnemyBoarClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy13_Zombie> EnemyZombieClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy22_Cultist> EnemyCultistClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy25_Sandworn> EnemySandBoxClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy28_Wasp> EnemyWaspClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy30_AttackDrone> EnemyDroneClass;

	// Special Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy9_Robot_Girl> EnemyRobotGirlClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy11_Robot_Executor> EnemyExucutorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy15_Bat_1> EnemyBatClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy19_Hunter_Sniper> EnemyHunterClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy27_Swat> EnemySwatClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy29_Scorpio> EnemyScorpioClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy31_KillerRabbit> EnemyKillerRaabitClass;

	// Elite Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy4_Parasite_Ultimate> EnemyParasiteUltimateClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy10_Robot_Papu> EnemyPapuClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy24_MiniBot> EnemyMiniBotClass;
	
	// Boss Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<class AEnemy26_Spider_Queen> EnemySpiderQueenClass;
	
	UFUNCTION(BlueprintCallable, Category = "Enemies")
		void RefreshEnemiesList();

	// nav system to get random location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		class UNavigationSystemV1* NavArea;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		FVector RandomLocationToSpawn;

	// variables for timer to spawn, it depends on difficulty
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		FTimerHandle SpawnTimerHandle;

	// Objectives -> 5 objectives, each one with a status and ftext
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Objective")
		EObjectiveStatus ObjectiveOneStatus = EObjectiveStatus::EUndiscovered;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Objective")
		FText ObjectiveOneContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Objective")
		EObjectiveStatus ObjectiveTwoStatus = EObjectiveStatus::EUndiscovered;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Objective")
		FText ObjectiveTwoContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Objective")
		EObjectiveStatus ObjectiveThreeStatus = EObjectiveStatus::EUndiscovered;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Objective")
		FText ObjectiveThreeContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Objective")
		EObjectiveStatus ObjectiveFourStatus = EObjectiveStatus::EUndiscovered;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Objective")
		FText ObjectiveFourContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Objective")
		EObjectiveStatus ObjectiveFiveStatus = EObjectiveStatus::EUndiscovered;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Objective")
		FText ObjectiveFiveContent;

public:
	ATrueProject2GameModeBase();

	virtual void BeginPlay() override;
	// virtual void Tick(float DeltaTime) override;

	// Game State
	/**Handle any function calls that rely upon changing the playing state of our game */
	
	UFUNCTION(BlueprintCallable, Category = "Game State")
		void HandleGameState();
	UFUNCTION(BlueprintCallable, Category = "Game State")
		void SetGameOver(EGameOverReason NewReason);

	// Time
	UFUNCTION(BlueprintCallable, Category = "Game Time")
		bool GetIsMorning();
	UFUNCTION(BlueprintCallable, Category = "Game Time")
		float GetCurrentSecond();
	UFUNCTION(BlueprintCallable, Category = "Game Time")
		float GetCurrentMinute();
	UFUNCTION(BlueprintCallable, Category = "Game Time")
		float GetCurrentHour();
	UFUNCTION(BlueprintCallable, Category = "Game Time")
		float GetCurrentDay();

	// Main Stats
	UFUNCTION(BlueprintCallable, Category = "Main")
		void GetMainLocation();
	UFUNCTION(BlueprintCallable, Category = "Main")
		void GetMainRotation();
	
	// Spawn Enemies Parameters
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		void SpawnEnemiesRandomly();
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		void GenerateRandomLocation();
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		bool CheckRandomLocationValid();
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		void SpawnEnemy();

protected:
	// InitGame Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString StartGameTXTENG = TEXT("Start Game");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString StartGameTXTChi = TEXT("开始游戏");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString StartGameTXTSpn = TEXT("Empezar");
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString OptionsTXTENG = TEXT("Options");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString OptionsTXTChi = TEXT("选项");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString OptionsTXTSpn = TEXT("Opciones");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString ExitTXTENG = TEXT("Exit");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString ExitTXTChi = TEXT("退出");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString ExitTXTSpn = TEXT("Salir");


	// Options Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString WindowModeTXTENG = TEXT("Window Mode");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString WindowModeTXTChi = TEXT("窗口模式");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString WindowModeTXTSpn = TEXT("Modo Ventaña");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString ResolutionTXTENG = TEXT("Resolution");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString ResolutionTXTChi = TEXT("分辨率");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString ResolutionTXTSpn = TEXT("Resolucion");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString GraphicsTXTENG = TEXT("Graphics");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString GraphicsTXTChi = TEXT("画质");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString GraphicsTXTSpn = TEXT("Grafico");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString VsyncTXTENG = TEXT("Vsync");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString VsyncTXTChi = TEXT("垂直同步");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString VsyncTXTSpn = TEXT("Sincronización Vertical");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString ApplyTXTENG = TEXT("Apply");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString ApplyTXTChi = TEXT("确定");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString ApplyTXTSpn = TEXT("Aplicar");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString BackTXTENG = TEXT("Go Back");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString BackTXTChi = TEXT("回退");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString BackTXTSpn = TEXT("Detras");

	// Pregame Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString NameTXTENG = TEXT("Name");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString NameTXTChi = TEXT("名字");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString NameTXTSpn = TEXT("Nombre");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString AgeTXTENG = TEXT("Age");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString AgeTXTChi = TEXT("年龄");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString AgeTXTSpn = TEXT("Edad");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString DescriptionTXTENG = TEXT("Character Description");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString DescriptionTXTChi = TEXT("介绍");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString DescriptionTXTSpn = TEXT("Descripcion");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString CustomizationTXTENG = TEXT("Customization");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString CustomizationTXTChi = TEXT("微调");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString CustomizationTXTSpn = TEXT("Personalización");

	// PlayerStats Widget
	// InGameMenu Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString ResumeTXTENG = TEXT("Resume");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString ResumeTXTChi = TEXT("恢复");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString ResumeTXTSpn = TEXT("Continuar");

		// options

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString QuitTXTENG = TEXT("Quit");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString QuitTXTChi = TEXT("退出");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString QuitTXTSpn = TEXT("Salir");
	
	// PostGame Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString MissionTXTENG = TEXT("Mission");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString MissionTXTChi = TEXT("任务");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString MissionTXTSpn = TEXT("Mision");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString WinTXTENG = TEXT("Win");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString WinTXTChi = TEXT("胜利");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString WinTXTSpn = TEXT("Completada");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString LoseTXTENG = TEXT("Lose");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString LoseTXTChi = TEXT("失败");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString LoseTXTSpn = TEXT("Fallida");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString DieReasonTXTENG = TEXT("Die Reason");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString DieReasonTXTChi = TEXT("死亡原因");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString DieReasonTXTSpn = TEXT("Razon de muerta");

		// reason of died

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString ItemCollectedTXTENG = TEXT("Items Collected");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString ItemCollectedTXTChi = TEXT("文物");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString ItemCollectedTXTSpn = TEXT("Artifactos coleccionados");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString StatsTXTENG = TEXT("Stats");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString StatsTXTChi = TEXT("数据");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString StatsTXTSpn = TEXT("Estatisticas");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString TimePlayedTXTENG = TEXT("Time Played");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString TimePlayedTXTChi = TEXT("总时间");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString TimePlayedTXTSpn = TEXT("Total Tiempo jugada");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString TotalDamageTXTENG = TEXT("Total Damage");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString TotalDamageTXTChi = TEXT("总伤害");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString TotalDamageTXTSpn = TEXT("Total Daño infringido");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString TotalEnemiesKilledTXTENG = TEXT("Total Enemies Killed");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString TotalEnemiesKilledTXTChi = TEXT("总杀敌数量");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString TotalEnemiesKilledTXTSpn = TEXT("Total Enemigos Eliminado");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString TotalXPTXTENG = TEXT("Total XP Learnt");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString TotalXPTXTChi = TEXT("总经验");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString TotalXPTXTSpn = TEXT("Total Experiencia ");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString TotalDamageTakenTXTENG = TEXT("Total Damage Taken");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString TotalDamageTakenTXTChi = TEXT("总受到伤害");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString TotalDamageTakenTXTSpn = TEXT("Total Daño Recibido");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString ItemsAmountTXTENG = TEXT("Total Items Collected");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString ItemsAmountTXTChi = TEXT("文物数量");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString ItemsAmountTXTSpn = TEXT("Cantidad de Artifacto");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display English")
		FString CommanderTXTENG = TEXT("Commander Comment");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Chinese")
		FString CommanderTXTChi = TEXT("教官总结");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Spanish")
		FString CommanderTXTSpn = TEXT("Comentario Del Comandante");

		// specific commander comment

	// Loading ???

};
