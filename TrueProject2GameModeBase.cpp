// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrueProject2GameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/Vector.h"
#include "NavigationSystem.h"
#include "TimerManager.h"

#include "Main.h"

// Enemies
#include "All_Enemies/EnemyClass.h"
#include "All_Enemies/BasicEnemy.h"
#include "All_Enemies/Enemy1_Bird.h"
#include "All_Enemies/Enemy2_Parasite_Baby.h"
#include "All_Enemies/Enemy3_Parasite_Rookie.h"
#include "All_Enemies/Enemy4_Parasite_Ultimate.h"
#include "All_Enemies/Enemy5_Human_Blade.h"
#include "All_Enemies/Enemy6_Human_Pistol.h"
#include "All_Enemies/Enemy7_Human_Shotgun.h"
#include "All_Enemies/Enemy8_Boar.h"
#include "All_Enemies/Enemy9_Robot_Girl.h"
#include "All_Enemies/Enemy10_Robot_Papu.h"
#include "All_Enemies/Enemy11_Robot_Executor.h"
#include "All_Enemies/Enemy13_Zombie.h"
#include "All_Enemies/Enemy15_Bat_1.h"
#include "All_Enemies/Enemy19_Hunter_Sniper.h"
#include "All_Enemies/Enemy22_Cultist.h"
#include "All_Enemies/Enemy24_MiniBot.h"
#include "All_Enemies/Enemy25_Sandworn.h"
#include "All_Enemies/Enemy26_Spider_Queen.h"
#include "All_Enemies/Enemy27_Swat.h"
#include "All_Enemies/Enemy28_Wasp.h"
#include "All_Enemies/Enemy29_Scorpio.h"
#include "All_Enemies/Enemy30_AttackDrone.h"
#include "All_Enemies/Enemy31_KillerRabbit.h"

ATrueProject2GameModeBase::ATrueProject2GameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATrueProject2GameModeBase::BeginPlay()
{
    Super::BeginPlay();

    InitializeAllVariables();

    // Game GameInstance
    GameInstance = Cast<UTrueGame2Instance>(UGameplayStatics::GetGameInstance(this));
    
    MainIsSpawned = false;

    // Spawn control
    SetMinRadio(500.0f);
    SetMaxRadio(15000.0f);
    SetSpawnRate(10.0f);

    // Process GameState
    HandleGameState();
}

// Called every frame
void ATrueProject2GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);    

    // GameMode is responsable to check if the main is dead or not, if dead -> quit by opening a new level
    if (MainIsSpawned)
    {
        if (IsValid(MainCharacter))
        {
            if (MainCharacter->GetCharacterHealth() <= 0.0f)
            {
                if (GameInstance)
                {
                    GameInstance->SetCurrentState(EGamePlayState::EGameOver);
                    HandleGameState();
                }
            }
        }
        else
        {
            if (GameInstance)
            {
                GameInstance->SetCurrentState(EGamePlayState::EGameOver);
                HandleGameState();
                // OpenPostGameState();
            }
        }
    }
}

void ATrueProject2GameModeBase::HandleGameState()
{
    if (GameInstance)
    {
        if (GameInstance->GetJustOpen())
        {
            OpenInitMenuWidget();
            GameInstance->SetJustOpen(false);
            
        }
        else
        {
            //Add the if logic of checking the first time opended
            switch (GameInstance->GetCurrentState())
            {
            case EGamePlayState::EPreparing:
            {
                // Open Init Menu Widget
                OpenPreGameWidget();
                break;
            }
            case EGamePlayState::EPlaying:
            {
                // Reset all values

                // Spawn Main
                SpawnMain();

                // Time control
                TimeRunning();

                // Spawn Enemies overtime
                SpawnEnemiesRandomly();
                break;

            }
            case EGamePlayState::EGameOver:
            {
                // Load all necesaries ststs in game instance
                PastAllPostGameStats();

                // Open Post Game Analisis Widget
                OpenPostGameWidget();
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

// In reality, there is not need to re initialized all variables
// as the only time these variables are needed is when the gamemode is in playing
void ATrueProject2GameModeBase::InitializeAllVariables()
{
    TotalGameTimeInSeconds = 0.0f;
    CurrentDayTimeInSeconds = 0.0f;
    dayTotalDuration = dayDuration + nightDuration;
    oneHourInGame = dayTotalDuration / 24.0f;
}

/* Game State
Each time a new level open -> the game mode override -> call GetGameMode() in order to
process what is going to do
*/
void ATrueProject2GameModeBase::OpenPreGameState()
{
    if (GameInstance)
    {
        // GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Open PreGameState"));
        GameInstance->SetCurrentState(EGamePlayState::EPreparing);
        UGameplayStatics::OpenLevel(this, FName("TruePreGameLevel"));
    }
}
void ATrueProject2GameModeBase::OpenPlayingState()
{
    if (GameInstance)
    {
        // GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Open InGameState"));
        GameInstance->SetCurrentState(EGamePlayState::EPlaying);
        UGameplayStatics::OpenLevel(this, FName("TrueTheGameLevel"));
    }
}
void ATrueProject2GameModeBase::OpenPostGameState()
{
    if (GameInstance)
    {
        // Open the level
        // GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Open PostGameState"));
        GameInstance->SetCurrentState(EGamePlayState::EGameOver);
        UGameplayStatics::OpenLevel(this, FName("TruePostGameLevel"));
    }
}

void ATrueProject2GameModeBase::PastAllPostGameStats()
{
    // Total Time
    GameInstance->SetTotalInGameSegs(TotalGameTimeInSeconds);
    
    // Main Stats
    MainCharacter->SetStatsToGameInstance();
}

// Time Control
void ATrueProject2GameModeBase::TimeRunning()
{
    CurrentDayTimeInSeconds += 1;
    dayTimePercentage = CurrentDayTimeInSeconds / dayTotalDuration;

    CheckTime();

    // run the world timer
    GetWorldTimerManager().SetTimer(RunTimerHandle, this,
        &ATrueProject2GameModeBase::TimeRunning, 1.0f, false);
}

// Check Time 
void ATrueProject2GameModeBase::CheckTime()
{
    // Manage day/ night circle
    if (CurrentDayTimeInSeconds == dayDuration)
    {
        // GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Morning finish"));
        // morning finish -> start the night
        bIsInMorning = false;
        HandleTime();

    }
    else if (CurrentDayTimeInSeconds == dayDuration + nightDuration)
    {
        // GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Night finish"));
        // night finish -> start a new day
        bIsInMorning = true;
        HandleTime();
    }

    // Manage real world time to display
    if (RealWorldTimeChanged())
    {
        RealWorldTimeConverter();
        GiveRealWorldTime();
    }

}

void ATrueProject2GameModeBase::HandleTime()
{
    if (bIsInMorning)
    {
        // Refresh enemies list
        RefreshEnemiesList();

        // when night finish -> the day and difficulty also change
        // Reset the difficulty of current enemies
        UpdateDifficulty();

        // Debuff all enemies spawned
        DebuffAllDayEnemies();
        
        // Day variables update
        daysCounter += 1;
        TotalGameTimeInSeconds += CurrentDayTimeInSeconds;
        CurrentDayTimeInSeconds = 0.0f;
        realWorldTime = 0.0f;
        dayTimePercentage = 0.0f;

    }
    else
    {
        // Buff to all enemies spawned -> detection, speed, damage, health
        // logic of buff enemies that will spawned is part of spawn enemies
        BuffAllNightEnemies();
    }
}

// FOR NOW -> It does not reset the difficulties of already spawned enemies
void ATrueProject2GameModeBase::BuffAllEnemiesByDifficulty()
{
    for (AEnemyClass* EnemyDelta : EnemiesSpawned)
    {
        if (IsValid(EnemyDelta))
        {
            BuffAEnemyByDifficulty(EnemyDelta);
        }
    }
}
void ATrueProject2GameModeBase::BuffAEnemyByDifficulty(AEnemyClass* AEnemy)
{
    if (IsValid(AEnemy))
    {
        // Buff to all enemies spawned -> detection, speed, damage, health
        AEnemy->UpdateHealthPoint(HealthMofByDifficulty);
        AEnemy->UpdateCharacterPowerUp(PowerMofByDifficulty);
    }
}
void ATrueProject2GameModeBase::ResetAllEnemiesDifficultyBuff()
{
    for (AEnemyClass* EnemyDelta : EnemiesSpawned)
    {
        if (IsValid(EnemyDelta))
        {
            ResetAEnemyDifficultyBuff(EnemyDelta);
        }
    }
}
void ATrueProject2GameModeBase::ResetAEnemyDifficultyBuff(AEnemyClass* AEnemy)
{
    if (IsValid(AEnemy))
    {
        // Buff to all enemies spawned -> detection, speed, damage, health
        AEnemy->UpdateHealthPoint(-HealthMofByDifficulty);
        AEnemy->UpdateCharacterPowerUp(-PowerMofByDifficulty);
    }
}

void ATrueProject2GameModeBase::BuffAllNightEnemies()
{
    for (AEnemyClass* EnemyDelta : EnemiesSpawned)
    {
        if (IsValid(EnemyDelta))
        {
            BuffANightEnemy(EnemyDelta);
        }
    }
}
void ATrueProject2GameModeBase::BuffANightEnemy(AEnemyClass* AEnemy)
{
    if (!bIsInMorning)
    {
        if (IsValid(AEnemy))
        {
            // Buff to all enemies spawned -> detection, speed, damage, health
            AEnemy->UpdateHealthPoint(HealthModifierByNight);
            AEnemy->UpdateCharacterPowerUp(PowerModifierByNight);
        }  
    }
}
void ATrueProject2GameModeBase::DebuffAllDayEnemies()
{
    for (AEnemyClass* EnemyDelta : EnemiesSpawned)
    {
        if (IsValid(EnemyDelta))
        {
            DebuffADayEnemy(EnemyDelta);
        }
    }
}
void ATrueProject2GameModeBase::DebuffADayEnemy(AEnemyClass* AEnemy)
{
    if (bIsInMorning)
    {
        if (IsValid(AEnemy))
        {
            // Debuff to all enemies spawned -> detection, speed, damage, health
            AEnemy->UpdateHealthPoint(-HealthModifierByNight);
            AEnemy->UpdateCharacterPowerUp(-PowerModifierByNight);
        }
    }
}

void ATrueProject2GameModeBase::UpdateDifficulty()
{
    difficulty = difficulty * difficultyModifier;

    HealthMofByDifficulty = HealthMofByDifficulty * difficulty;
    PowerMofByDifficulty = PowerMofByDifficulty * difficulty;
    EnemySpawnRate = EnemySpawnRate * (1 / difficulty);
}

// Main Stats
void ATrueProject2GameModeBase::SpawnMain()
{
    // ***** Need to add logic about where spawn player and not just restart it
    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    //MainHalfHeight = MainCharacter->GetMainHalfHeight();
    float MainHalfHeight = 200.0f;
    FVector PlaceToSpawnMain = FVector(100.0f, 100.0f, 100.0f) + FVector(0.0f, 0.0f, MainHalfHeight);

    MainCharacter = GetWorld()->SpawnActor<AMain>(MainClass, PlaceToSpawnMain, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    if (PlayerController && MainCharacter)
    {
        PlayerController->Possess(MainCharacter);
        MainIsSpawned = true;
        MainCharacter->InitializeMainController();
        // GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Spawn and Possesed Main"));
    }

    PlayerHUD = MainCharacter->GetPlayerUIWidget();
}

void ATrueProject2GameModeBase::GetMainLocation()
{
    if (IsValid(MainCharacter))
    {
        PlayerLocation = MainCharacter->GetPlayerPosition();
    }
}
void ATrueProject2GameModeBase::GetMainRotation()
{
    if (IsValid(MainCharacter))
    {
        PlayerRotation = MainCharacter->GetPlayerRotation();
    }
}

// Spawn Enemies
void ATrueProject2GameModeBase::SpawnEnemiesRandomly()
{
    GetMainLocation();
    GetMainRotation();

    GenerateRandomLocation();
    if (CheckRandomLocationValid())
    {
        SpawnEnemy();
    }

    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ATrueProject2GameModeBase::SpawnEnemiesRandomly, EnemySpawnRate, false);
}

void ATrueProject2GameModeBase::GenerateRandomLocation()
{
    NavArea = FNavigationSystem::
        GetCurrent<UNavigationSystemV1>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    if (NavArea)
    {
        NavArea->K2_GetRandomReachablePointInRadius(GetWorld(),
            PlayerLocation, RandomLocationToSpawn, maxRadio);
    }

    RandomLocationToSpawn = RandomLocationToSpawn + FVector(0.0f, 0.0f, SpawnOffset);

}

bool ATrueProject2GameModeBase::CheckRandomLocationValid()
{
    DistOfRandom = (PlayerLocation - RandomLocationToSpawn).Size();

    return minRadio <= DistOfRandom;
}

void ATrueProject2GameModeBase::SpawnEnemy()
{
    // Change the rotation -> should be spawnLocation - ActorLocation
    // have to spawn based on rarity just like miniworld
    AEnemyClass* aRandomEnemy = GetRandomEnemy();

    // When a enemy spawn -> update its stats by difficulty and night if it is night
    EnemiesSpawned.Add(aRandomEnemy);
    
    BuffAEnemyByDifficulty(aRandomEnemy);
    if (!bIsInMorning)
    {
        BuffANightEnemy(aRandomEnemy);
    }
}

AEnemyClass* ATrueProject2GameModeBase::GetRandomEnemy() {
    
    EEnemyRarity EnemyRarity = GenerateRandomEnemyRarity();
    AEnemyClass* theRandomEnemy;

    switch (EnemyRarity) {
        case EEnemyRarity::ENormal: {
            theRandomEnemy = GenerateNormalEnemy();
            break;
        }
        case EEnemyRarity::ESpecial: {
            theRandomEnemy = GenerateSpecialEnemy();
            break;
        }
        case EEnemyRarity::EElite: {
            theRandomEnemy = GenerateEliteEnemy();
            break;
        }
        case EEnemyRarity::EBoss: {
            theRandomEnemy = GenerateBossEnemy();
            break;
        }
        default:
        {
            theRandomEnemy = GenerateNormalEnemy();
            break;
        }
                }

    return theRandomEnemy;
}

EEnemyRarity ATrueProject2GameModeBase::GenerateRandomEnemyRarity() {
    int Chance = FMath::RandRange(1, 100);
    
    /*
    * 60% -> normal enemy
    * 30% -> special enemy
    * 9% -> elite enemy
    * 1% -> boss enemy
    * 0% -> giga boss enemy
    */
    if (Chance < 60) {
        return EEnemyRarity::ENormal;
    }
    else if (Chance < 90) {
        return EEnemyRarity::ESpecial;
    }
    else if (Chance < 90) {
        return EEnemyRarity::EElite;
    }
    else {
        return EEnemyRarity::EBoss;
    }
}

/* Rarity per enemy
Normal -> 12
1: Bird -> Normal
2: Parasite Baby -> Normal
3: Parasite Rookie -> Normal
5: Robot Blade -> Normal
6: Human pistol -> Nomral
7: Human shotgun -> Normal
8: Boar -> Normal
22: Cultist -> Normal
13: Zombie -> Normal
25: Sandworm -> Normal
28: Wasp -> Normal
30: Attack Drone -> Normal

Special -> 7
9: Robot girl -> Special
11: Robot executor -> Special
15: Bat -> Special
19: Hunter sniper -> Special
27: Swat -> Special
29: Scorpio -> Special
31: Rabbit -> Special

Elite -> 3
4: Parasite Ultimate -> Elite
10: Robot Papu -> Elite
24: Minibot -> Elite

Boss -> 1
26: Spider queen -> Boss
*/

AEnemyClass* ATrueProject2GameModeBase::GenerateNormalEnemy() {
    int chosenNumber = FMath::RandRange(1, normalEnemy);

    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


    switch (chosenNumber) {
        case 1: {
            if (IsValid(EnemyBirdClass)) {
                return GetWorld()->SpawnActor<AEnemy1_Bird>(EnemyBirdClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 2: {
            if (IsValid(EnemyParasiteBabyClass)) {
                return GetWorld()->SpawnActor<AEnemy2_Parasite_Baby>(EnemyParasiteBabyClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 3: {
            if (IsValid(EnemyParasiteRookieClass)) {
                return GetWorld()->SpawnActor<AEnemy3_Parasite_Rookie>(EnemyParasiteRookieClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 4: {
            if (IsValid(EnemyHumanBladeClass)) {
                return GetWorld()->SpawnActor<AEnemy5_Human_Blade>(EnemyHumanBladeClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 5: {
            if (IsValid(EnemyHumanPistolClass)) {
                return GetWorld()->SpawnActor<AEnemy6_Human_Pistol>(EnemyHumanPistolClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 6: {
            if (IsValid(EnemyHumanShotgunClass)) {
                return GetWorld()->SpawnActor<AEnemy7_Human_Shotgun>(EnemyHumanShotgunClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 7: {
            if (IsValid(EnemyBoarClass)) {
                return GetWorld()->SpawnActor<AEnemy8_Boar>(EnemyBoarClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 8: {
            if (IsValid(EnemyZombieClass)) {
                return GetWorld()->SpawnActor<AEnemy13_Zombie>(EnemyZombieClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 9: {
            if (IsValid(EnemyCultistClass)) {
                return GetWorld()->SpawnActor<AEnemy22_Cultist>(EnemyCultistClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 10: {
            if (IsValid(EnemySandBoxClass)) {
                return GetWorld()->SpawnActor<AEnemy25_Sandworn>(EnemySandBoxClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 11: {
            if (IsValid(EnemyWaspClass)) {
                return GetWorld()->SpawnActor<AEnemy28_Wasp>(EnemyWaspClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 12: {
            if (IsValid(EnemyDroneClass)) {
                return GetWorld()->SpawnActor<AEnemy30_AttackDrone>(EnemyDroneClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }/*
        default: {
            return GetWorld()->SpawnActor<AEnemy1_Bird>(EnemyBirdClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            break;
        }*/
    }
    return GetWorld()->SpawnActor<AEnemy1_Bird>(EnemyBirdClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
}

AEnemyClass* ATrueProject2GameModeBase::GenerateSpecialEnemy() {
    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    return GetWorld()->SpawnActor<AEnemy1_Bird>(EnemyBirdClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
}

AEnemyClass* ATrueProject2GameModeBase::GenerateEliteEnemy() {
    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    return GetWorld()->SpawnActor<AEnemy1_Bird>(EnemyBirdClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
}

AEnemyClass* ATrueProject2GameModeBase::GenerateBossEnemy() {
    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    return GetWorld()->SpawnActor<AEnemy1_Bird>(EnemyBirdClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
}


void ATrueProject2GameModeBase::SetMinRadio(float radioValue)
{
    minRadio = radioValue;
}
void ATrueProject2GameModeBase::SetMaxRadio(float radioValue)
{
    maxRadio = radioValue;
}
void ATrueProject2GameModeBase::SetSpawnRate(float newSpawnRate)
{
    EnemySpawnRate = newSpawnRate;
}

void ATrueProject2GameModeBase::RefreshEnemiesList()
{
    for (AEnemyClass* EnemyDelta : EnemiesSpawned)
    {
        if (!IsValid(EnemyDelta))
        {
            EnemiesSpawned.Remove(EnemyDelta);
        }
    }
}

// this method only work if the total time duration is multiple of 24
bool ATrueProject2GameModeBase::RealWorldTimeChanged()
{
    return CurrentDayTimeInSeconds % oneHourInGame == 0.0f;
}
void ATrueProject2GameModeBase::RealWorldTimeConverter()
{
    realWorldTime = CurrentDayTimeInSeconds / oneHourInGame;
}

// Time Stats for display
float ATrueProject2GameModeBase::GiveTimePercentage()
{
    return dayTimePercentage;
}

FText ATrueProject2GameModeBase::GiveRealWorldTime()
{
    int32 TimePercentage = FMath::RoundHalfFromZero(dayTimePercentage * 100);
    FString TimePercentageString = FString::FromInt(TimePercentage);
    FString TimePercentageHUD = TimePercentageString + FString(TEXT(":00"));
    FText TimePercentageTEXT = FText::FromString(TimePercentageHUD);
    return TimePercentageTEXT;
}