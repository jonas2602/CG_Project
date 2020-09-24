// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class CG_PROJECT_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
	/************ IGenericTeamAgentInterface Start *************/
public:
	/** Retrieved owner attitude toward given Other object */
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	/** Assigns Team Agent to given TeamID */
	UFUNCTION(BlueprintCallable, Category = "Diplomacy")
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	/** Retrieve team identifier in form of FGenericTeamId */
	UFUNCTION(BlueprintCallable, Category = "Diplomacy")
	virtual FGenericTeamId GetGenericTeamId() const override;
	/************ IGenericTeamAgentInterface End *************/
	
	
};
