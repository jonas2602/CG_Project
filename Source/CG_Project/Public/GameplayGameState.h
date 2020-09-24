// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameplayGameState.generated.h"

/**
 * 
 */
UCLASS()
class CG_PROJECT_API AGameplayGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Player", Meta = (WorldContext = "WorldContextObject"))
	static EPlayerRole GetLocalPlayerRole(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Player", Meta = (WorldContext = "WorldContextObject"))
	static bool LocalPlayerHasRole(UObject* WorldContextObject, EPlayerRole PlayerRole);

	UFUNCTION(BlueprintCallable, Category = "Player", Meta = (ExpandEnumAsExecs = "Branches", WorldContext = "WorldContextObject"))
	static void SwitchLocalPlayerRole(UObject* WorldContextObject, EPlayerRole& Branches);
};
