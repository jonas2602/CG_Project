// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPawnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IPawnInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Client , Reliable, BlueprintCallable, Category = "Pawn")
	virtual void Init(AController* NewController);
	
	UFUNCTION(Client , Reliable, BlueprintCallable, Category = "Pawn")
	virtual void Deinit(AController* OldController);
};
