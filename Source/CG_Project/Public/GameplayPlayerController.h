// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.h"
#include "GameFramework/PlayerController.h"
#include "GameplayPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CG_PROJECT_API AGameplayPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void OnPossess(APawn* Pawn) override;
	virtual void OnUnPossess() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Default")
	EPlayerRole GetPlayerRole() { return PlayerInfo.PlayerRole; }

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Default")
	FPlayerInfo PlayerInfo;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Default")
	APawn* PreviousPawn;
};
