// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayPlayerController.h"
#include "PawnInterface.h"
#include "GameFramework/Pawn.h"



void AGameplayPlayerController::OnPossess(APawn* Pawn)
{
	Super::OnPossess(Pawn);

	// UE_LOG(LogClass, Error, TEXT("Possess controller"));
	/*if (Pawn->GetClass()->ImplementsInterface(UPawnInterface::StaticClass()))
	{
		IPawnInterface::Execute_Init(Pawn, this);
	}*/
}

void AGameplayPlayerController::OnUnPossess()
{
	PreviousPawn = GetPawn();

	Super::OnUnPossess();
}
