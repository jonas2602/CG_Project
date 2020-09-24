// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerInfo.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsMenuWidget.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CG_PROJECT_API UOptionsMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

protected:
	// UPROPERTY(BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn = "true"))
	// FPlayerInfo PlayerInfo;
	
	
};
