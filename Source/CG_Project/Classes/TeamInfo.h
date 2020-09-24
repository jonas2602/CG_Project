// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "TeamInfo.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ETeam : uint8
{
	Team1 = 0,
	Team2 = 1,
	Monster = 2
};

