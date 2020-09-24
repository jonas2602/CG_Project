// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Private/InteractionInterface.h"
#include "BaseCharacter.h"
#include "SupportDrone.generated.h"

class UWidgetComponent;
class UFunctionWidget;

UCLASS()
class CG_PROJECT_API ASupportDrone : public ABaseCharacter, public IInteractionInterface
{
	GENERATED_BODY()

	// Interaction Widget as visible Highlight for the Thief
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* ThiefWidget;

	// Interaction Widget as visible Highlight for the Supporter
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* SupporterWidget;

public:
	// Sets default values for this character's properties
	ASupportDrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Interaction")
	void PossessedHandler(AController* NewController);
	void PossessedHandler_Implementation(AController* NewController);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/************ Interaction Interface Start *************/
public:
	virtual void Interact_Implementation(AActor* Interactor) override;
	virtual void ToggleThiefWidget_Implementation(bool Highlight) override;
	virtual void ToggleSupporterWidget_Implementation(bool Highlight) override;
	virtual FVector GetInteractionLocation_Implementation() override;
	virtual bool CanInteract_Implementation(AActor* Interactor) override;

protected:
	virtual void SetupThiefWidgetText_Implementation(const FText& Text);
	virtual void SetupThiefWidget_Implementation();
	virtual void SetupSupporterWidget_Implementation();

	// Offset from Actor Origin
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		FVector WidgetOffset = FVector(0.0f, 0.0f, 100.0f);

	// description visible in interaction ui
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		FText WidgetDescription = FText::FromString("Interact");

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		bool CanInteract = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TArray<TSubclassOf<UFunctionWidget>> FunctionClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* CenterImage;
	/************* Interaction Interface End **************/
};
