// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Classes/TeamInfo.h"
#include "GenericTeamAgentInterface.h"
#include "BaseCharacter.generated.h"

UCLASS()
class CG_PROJECT_API ABaseCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/************ IGenericTeamAgentInterface Start *************/
protected:
	UPROPERTY(VisibleAnywhere, Category = "Diplomacy")
	FGenericTeamId TeamID;

	UPROPERTY(EditAnywhere, Category = "Diplomacy")
	ETeam InitialTeam;

public:
	/** Assigns Team Agent to given TeamID */
	UFUNCTION(BlueprintCallable, Category = "Diplomacy")
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override { TeamID = NewTeamID; };

	/** Retrieve team identifier in form of FGenericTeamId */
	UFUNCTION(BlueprintCallable, Category = "Diplomacy")
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }
	/************ IGenericTeamAgentInterface End *************/
	
};
