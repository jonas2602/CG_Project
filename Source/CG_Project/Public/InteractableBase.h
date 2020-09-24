// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "private/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

class UBillboardComponent;
class UWidgetComponent;
class UStaticMeshComponent;
class UFunctionWidget;

UCLASS()
class CG_PROJECT_API AInteractableBase : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

		// Billboard as Root Component
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable", meta = (AllowPrivateAccess = "true"))
		UBillboardComponent* RootBillboard;

	// Interaction Widget as visible Highlight for the Thief
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* ThiefWidget;

	// Interaction Widget as visible Highlight for the Supporter
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* SupporterWidget;

protected:
	// Static mesh to represent the pickup in the level
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interactable", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* InteractableMesh;

public:
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;


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
		TArray<TSubclassOf<UFunctionWidget>> FunctionClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* CenterImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, /*Replicated,*/ Category = "UI")
	bool CanInteract = true;
	/************* Interaction Interface End **************/
};
