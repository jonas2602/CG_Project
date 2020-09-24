// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "GameplayPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "UnrealNetwork.h"

void AGameplayGameMode::RespawnPlayer_Implementation(APlayerController* Controller, TSubclassOf<APawn> PawnClass)
{
	// Get Currently controlled Pawn and Destroy
	APawn* ControlledPawn = Controller->GetPawn();
	if (ControlledPawn)
	{
		ControlledPawn->Destroy();
	}

	// Validate passed Pawn
	if (PawnClass == nullptr)
	{
		UE_LOG(LogClass, Warning, TEXT("Character not valid, spawn default pawn"));
		PawnClass = DefaultPawnClass;
	}

	// Get Spawn Point to Spawn the new Pawn at
	TArray<AActor*> FoundSpawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundSpawns);
	if (FoundSpawns.Num() == 0)
	{
		UE_LOG(LogClass, Error, TEXT("No PlayerStart found to Spawn at"));
		return;
	}


	// Spawn Pawn and Posses
	FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.Owner = Controller;
	APawn* NewPawn = GetWorld()->SpawnActor<APawn>(PawnClass, FoundSpawns[0]->GetActorTransform(), SpawnParams);
	Controller->Possess(NewPawn);
	UE_LOG(LogClass, Error, TEXT("%s possessed %s"), *Controller->GetName(), *NewPawn->GetName());
}

bool AGameplayGameMode::RespawnPlayer_Validate(APlayerController* Controller, TSubclassOf<APawn> PawnClass)
{
	return true;
}
