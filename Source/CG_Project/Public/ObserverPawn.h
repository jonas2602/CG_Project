// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "ObserverPawn.generated.h"

/**
 * 
 */
UCLASS()
class CG_PROJECT_API AObserverPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Interaction")
	void PossessedHandler(AController* NewController);
	void PossessedHandler_Implementation(AController* NewController);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Interaction")
	void UnpossessedHandler(AController* OldController);
	void UnpossessedHandler_Implementation(AController* OldController);
	
	
};
