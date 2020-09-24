// Fill out your copyright notice in the Description page of Project Settings.

#include "ObserverPawn.h"
#include "GameplayPlayerController.h"
#include "Engine/World.h"




void AObserverPawn::PossessedHandler_Implementation(AController* NewController)
{
	AGameplayPlayerController* GameplayPC = Cast<AGameplayPlayerController>(NewController);
	if (GameplayPC == nullptr)
	{
		return;
	}

	// Disable Camera Rotation
	GameplayPC->InputYawScale = 0;
	GameplayPC->InputPitchScale = 0;
	GameplayPC->InputRollScale = 0;

	// Set Camera Rotation
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));

	// Set Input Mode
	GameplayPC->bShowMouseCursor = true;
	FInputModeGameAndUI mode = FInputModeGameAndUI();
	mode.SetHideCursorDuringCapture(false);
	GameplayPC->SetInputMode(mode);
}

void AObserverPawn::UnpossessedHandler_Implementation(AController* OldController)
{
	AGameplayPlayerController* GameplayPC = Cast<AGameplayPlayerController>(OldController);
	if (GameplayPC == nullptr)
	{
		return;
	}
	
	// UE_LOG(LogClass, Error, TEXT("Unpossess %s"), GetWorld()->IsServer() ? TEXT("Server") : TEXT("Client"));

	// Reactivate Camera Rotation
	GameplayPC->InputYawScale = 2.5f;
	GameplayPC->InputPitchScale = -1.75f;
	GameplayPC->InputRollScale = 1.0f;
}