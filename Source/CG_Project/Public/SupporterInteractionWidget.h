// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SupporterInteractionWidget.generated.h"

class UFunctionWidget;
class AInteractableBase;

/**
*
*/
UCLASS()
class CG_PROJECT_API USupporterInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void Setup(const TArray<TSubclassOf<UFunctionWidget>>& FunctionClasses, AActor* Interactable, UTexture2D* CenterImage);
	virtual void Setup_Implementation(TArray<TSubclassOf<UFunctionWidget>> FunctionClasses, AActor* Interactable, UTexture2D* CenterImage) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void FadeIn();
	virtual void FadeIn_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void FadeOut();
	virtual void FadeOut_Implementation() {};

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void AddFunctionWidget(TSubclassOf<UFunctionWidget> WidgetClass, AActor* Interactable);
	virtual void AddFunctionWidget_Implementation(TSubclassOf<UFunctionWidget> WidgetClass, AActor* Interactable) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void ClearFunctionWidgets();
	virtual void ClearFunctionWidgets_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void FadeInStep();
	virtual void FadeInStep_Implementation() {};
};
