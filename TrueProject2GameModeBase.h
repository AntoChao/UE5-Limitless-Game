// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TrueGame2Instance.h"
#include "Common_Enums.h"
#include "TrueProject2GameModeBase.generated.h"

UCLASS()
class TRUEPROJECT2_API ATrueProject2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Game necesary values
	UFUNCTION(BlueprintCallable, Category = "GameState")
		void InitializeAllVariables();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance")
		UTrueGame2Instance* GameInstance;

	/*
	GameMode start by reading GameInstance game state
	which is left by the previous GAMEMODE
	GameMode should finish by leaving the next game state and opening the correspond level
	*/
	UFUNCTION(BlueprintCallable, Category = "GameState")
		void OpenPreGameState();
	UFUNCTION(BlueprintCallable, Category = "GameState")
		void OpenPlayingState();
	UFUNCTION(BlueprintCallable, Category = "GameState")
		void OpenPostGameState();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Open Widget")
		void OpenInitMenuWidget();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Open Widget")
		void OpenPreGameWidget();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Open Widget")
		void OpenPostGameWidget();

	// Past PostGame Stats
	UFUNCTION(BlueprintCallable, Category = "Game State")
		void PastAllPostGameStats();

	// Game Timer
		// difficulty of the current stage, difficulty is update by timer and event
		// Difficulty -> change the power, health and spawn frequency
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float difficulty = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float difficultyModifier = 1.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float HealthMofByDifficulty = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float PowerMofByDifficulty = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		float EnemySpawnRate;

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void UpdateDifficulty();
	
	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void BuffAllEnemiesByDifficulty();
	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void BuffAEnemyByDifficulty(AEnemyClass* AEnemy);
	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void ResetAllEnemiesDifficultyBuff();
	UFUNCTION(BlueprintCallable, Category = "Difficulty")
		void ResetAEnemyDifficultyBuff(AEnemyClass* AEnemy);

	// Modifiers for spwaning
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float HealthModifierDifficulty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Difficulty")
		float PowerModifierDifficulty;

	// Time/ day control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		FTimerHandle RunTimerHandle;
	/*Somehow I have to change this value to realistic -> I only have to change it to hours*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		int TotalGameTimeInSeconds; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		int CurrentDayTimeInSeconds = 0.0f;;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		int daysCounter = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		bool bIsInMorning = true; /*day or night*/

	// Suppose day = 60 segs and night = 10segs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		int dayTotalDuration = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		int dayDuration = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		int nightDuration = 4.0f;
	
	// For displaying purpose
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		int oneHourInGame = 0.0f; /*totalDayDuration / 24 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		int realWorldTime = 0.0f; /*mim 0, max = 23*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time State")
		float dayTimePercentage = 0.0f;


	// Time/ Day
	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void TimeRunning();
	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void CheckTime();
	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void HandleTime();

		// to display
	UFUNCTION(BlueprintCallable, Category = "Time State")
		bool RealWorldTimeChanged();
	UFUNCTION(BlueprintCallable, Category = "Time State")
		void RealWorldTimeConverter();


	// Buff/ Debuff enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff/Debuff")
		float HealthModifierByNight = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff/Debuff")
		float PowerModifierByNight = 0.0f;
	
	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void BuffAllNightEnemies();
	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void BuffANightEnemy(AEnemyClass* AEnemy);

	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void DebuffAllDayEnemies();
	UFUNCTION(BlueprintCallable, Category = "Buff/Debuff")
		void DebuffADayEnemy(AEnemyClass* AEnemy);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		TSubclassOf<class UPlayerStatsUMG> PlayerHUDClass;

	// Enemies To Recognize
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		float SpawnOffset = 50.0f;
	// All Enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		TArray<AEnemyClass*> EnemiesSpawned = {};
	
	/*
	ENormal,
	ESpecial,
	EElite,
	EBoss,
	EGigaBoss,
	EUnknown
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		int enemyRarities = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		int normalEnemy = 12;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		int specialEnemy = 7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		int eliteEnemy = 3;
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

	// radios to determinate the spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		float minRadio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		float maxRadio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Enemies")
		float DistOfRandom;

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
	virtual void Tick(float DeltaTime) override;

	// Game State
	/**Handle any function calls that rely upon changing the playing state of our game */
	UFUNCTION(BlueprintCallable, Category = "Game State")
		void HandleGameState();

	// Main Stats
	UFUNCTION(BlueprintCallable, Category = "Main")
		void GetMainLocation();
	UFUNCTION(BlueprintCallable, Category = "Main")
		void GetMainRotation();
	
	// Spawn parameters
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		void SetMinRadio(float radioValue);
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		void SetMaxRadio(float radioValue);
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		void SetSpawnRate(float newSpawnRate);
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		void SpawnEnemiesRandomly();
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		void GenerateRandomLocation();
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		bool CheckRandomLocationValid();
	UFUNCTION(BlueprintCallable, Category = "Spawn Enemies")
		void SpawnEnemy();

	// Time
	UFUNCTION(BlueprintCallable, Category = "Time Stats")
		float GiveTimePercentage();

	UFUNCTION(BlueprintCallable, Category = "Time Stats")
		FText GiveRealWorldTime();
	
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
