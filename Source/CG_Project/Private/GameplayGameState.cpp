// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayGameState.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "GameplayPlayerController.h"
#include "PlayerInfo.h"

EPlayerRole AGameplayGameState::GetLocalPlayerRole(UObject* WorldContextObject)
{
	AGameplayPlayerController* LocalController = Cast<AGameplayPlayerController>(WorldContextObject->GetWorld()->GetFirstLocalPlayerFromController()->PlayerController);
	if (LocalController == nullptr)
	{
		UE_LOG(LogClass, Error, TEXT("No Local Player found"));
		return EPlayerRole::Thief;
	}

	return LocalController->GetPlayerRole();
}

bool AGameplayGameState::LocalPlayerHasRole(UObject* WorldContextObject, EPlayerRole PlayerRole)
{
	return GetLocalPlayerRole(WorldContextObject) == PlayerRole;
}

void AGameplayGameState::SwitchLocalPlayerRole(UObject* WorldContextObject, EPlayerRole& Branches)
{
	Branches = GetLocalPlayerRole(WorldContextObject);
}


