// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FunctionWidget.generated.h"


/**
*
*/
UCLASS(abstract)
class CG_PROJECT_API UFunctionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Default")
		void Setup(AActor* InteractableOwner);
		virtual void Setup_Implementation(AActor* InteractableOwner);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
		AActor* InteractableOwner;

};
