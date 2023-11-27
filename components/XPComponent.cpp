// Fill out your copyright notice in the Description page of Project Settings.


#include "XPComponent.h"

// Sets default values for this component's properties
UXPComponent::UXPComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UXPComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Process XP Logic -> by abilityFeedBack or KillFeedBack
void UXPComponent::ReceiveXP(int amountXP)
{
	xp += amountXP;
	current_total += amountXP;
	xp_total_gain += amountXP;
	
	// check if the player do not abuse the buy
	if (level == 1 && xp < 0)
	{
		xp = 0;
	}
	else
	{
		while (IsAbleToLevelUp() || IsAbleToLevelDown())
		{
			// xp should be decrease or increase
			if (IsAbleToLevelUp())
			{
				// level up
				LevelUp();
			}
			else if (IsAbleToLevelDown())
			{
				LevelDown();
			}
		}
	}
}


// if xp > xp required
bool UXPComponent::IsAbleToLevelUp()
{
	return xp >= xp_required;
}
bool UXPComponent::IsAbleToLevelDown()
{
	return xp < 0;
}

// when the player decided to upgrade 1 ability, spend all xp needed and remain the rest and cost more 
void UXPComponent::LevelUp()
{
	if (IsAbleToLevelUp())
	{
		// Update level
		level += 1;

		// calculate the rest xp
		xp = xp - xp_required;
		
		// Update the xp requirement
		UpdateXPRequirement();
	}
}
void UXPComponent::LevelDown()
{
	if (IsAbleToLevelDown())
	{
		// Update Down 1 level
		level -= 1;

		// Update the xp requirement
		UpdateXPRequirement();

		// the x is negative, so just add it
		xp = xp_required + xp;
	}
}

void UXPComponent::UpdateXPRequirement()
{
	// need an formula for calculation that not include xp_required as variable
	xp_required = level * XPRatio;
}

bool UXPComponent::isAbleToBuy(int amountXP)
{
	return current_total > amountXP;
}

float UXPComponent::GetXPPercentage()
{
	return xp / xp_required *100;
}

FText UXPComponent::GetLevelText()
{
	FString LevelString = FString::FromInt(level);

	return FText::FromString(LevelString);
}

void UXPComponent::SetXP(float xpAmount)
{
	xp = xpAmount;
}
float UXPComponent::GetXP()
{
	return xp;
}