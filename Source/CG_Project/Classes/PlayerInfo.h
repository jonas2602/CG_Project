// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "PlayerInfo.generated.h"

/**
 * 
 */

class APawn;

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
	Thief,
	Observer
};

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerInfo")
	FText PlayerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerInfo")
	EPlayerRole PlayerRole;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerInfo")
	TSubclassOf<APawn> PlayerCharacter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerInfo")
	TArray<int> SucceededLevelList;
};

UCLASS()
class UPlayerInfoFunctionLibrary : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "MissionInfo")
	static bool IsValid(const FPlayerInfo& Info)
	{
		return !Info.PlayerName.IsEmpty();
	}
};
