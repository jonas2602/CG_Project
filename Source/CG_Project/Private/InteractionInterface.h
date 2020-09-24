// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
*
*/
class IInteractionInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
		void Interact(AActor* Interactor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
		void ToggleThiefWidget(bool Highlight);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
		void ToggleSupporterWidget(bool Highlight);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
		FVector GetInteractionLocation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
		bool CanInteract(AActor* Interactor);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI")
		void SetupThiefWidgetText(const FText& Text);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI")
		void SetupThiefWidget();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI")
		void SetupSupporterWidget();
};
