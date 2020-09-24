// Fill out your copyright notice in the Description page of Project Settings.

#include "SupportDrone.h"
#include "InteractionWidget.h"
#include "SupporterInteractionWidget.h"
#include "FunctionWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayGameState.h"
#include "Engine/World.h"
#include "GameplayPlayerController.h"


// Sets default values
ASupportDrone::ASupportDrone()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	// Create the Interaction Widget components
	ThiefWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ThiefWidget"));
	ThiefWidget->SetupAttachment(RootComponent);
	SupporterWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SupporterWidget"));
	SupporterWidget->SetupAttachment(RootComponent);

	// Setup Interaction Widget
	IInteractionInterface::Execute_SetupThiefWidget(this);
}

// Called when the game starts or when spawned
void ASupportDrone::BeginPlay()
{
	Super::BeginPlay();

	// Setup Interaction-things
	IInteractionInterface::Execute_SetupThiefWidgetText(this, WidgetDescription);
	IInteractionInterface::Execute_ToggleThiefWidget(this, false);

	IInteractionInterface::Execute_SetupSupporterWidget(this);

	IInteractionInterface::Execute_ToggleSupporterWidget(this, AGameplayGameState::LocalPlayerHasRole(this, EPlayerRole::Observer));
}

// Called every frame
void ASupportDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASupportDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASupportDrone::PossessedHandler_Implementation(AController* NewController)
{
	AGameplayPlayerController* GameplayPC = Cast<AGameplayPlayerController>(NewController);
	if (GameplayPC == nullptr)
	{
		return;
	}

	GameplayPC->SetInputMode(FInputModeGameOnly());
	GameplayPC->bShowMouseCursor = false;
}

/************ Interaction_Interface Start *************/
void ASupportDrone::Interact_Implementation(AActor* Interactor)
{
	UE_LOG(LogClass, Warning, TEXT("%s starts interacting with %s"), *Interactor->GetName(), *GetName());
}

void ASupportDrone::ToggleThiefWidget_Implementation(bool Highlight)
{
	if (ThiefWidget->GetUserWidgetObject() == nullptr)
	{
		UE_LOG(LogClass, Error, TEXT("No Supporter Widget setup on %s"), *GetClass()->GetName());
		return;
	}

	if (ThiefWidget)
	{
		ThiefWidget->SetVisibility(Highlight);
	}
	// UE_LOG(LogClass, Warning, TEXT("%s set InteractionWidget visible? %d"), *GetName(), InteractionWidget->bVisible);
}

void ASupportDrone::ToggleSupporterWidget_Implementation(bool Highlight)
{
	// Widget Setup?
	USupporterInteractionWidget* SupporterInteractionWidget = Cast<USupporterInteractionWidget>(SupporterWidget->GetUserWidgetObject());
	if (SupporterInteractionWidget == nullptr)
	{
		UE_LOG(LogClass, Error, TEXT("No Supporter Widget setup on %s"), *GetClass()->GetName());
		return;
	}

	if (SupporterWidget)
	{
		// UE_LOG(LogClass, Error, TEXT("Highlight Drone Supporter Widget %s"), Highlight ? TEXT("true"): TEXT("false"));
		SupporterWidget->SetVisibility(Highlight);
	}
	// UE_LOG(LogClass, Warning, TEXT("%s set InteractionWidget visible? %d"), *GetName(), InteractionWidget->bVisible);

	if (Highlight)
	{
		SupporterInteractionWidget->FadeIn();
	}
	else
	{
		SupporterInteractionWidget->FadeOut();
	}
}

FVector ASupportDrone::GetInteractionLocation_Implementation()
{
	return ThiefWidget->GetComponentLocation();
}

bool ASupportDrone::CanInteract_Implementation(AActor* Interactor)
{
	return CanInteract;
}

void ASupportDrone::SetupThiefWidgetText_Implementation(const FText& Text)
{
	// Get Widget from Component
	UInteractionWidget* ThiefInteractionWidget = Cast<UInteractionWidget>(ThiefWidget->GetUserWidgetObject());
	if (ThiefInteractionWidget == nullptr)
	{
		UE_LOG(LogClass, Error, TEXT("No Thief Widget setup on %s"), *GetClass()->GetName());
	}

	// Setup Text
	ThiefInteractionWidget->SetInteractionText(Text);
	// UE_LOG(LogClass, Log, TEXT("InteractionWidget TextSetup successful"));
}

void ASupportDrone::SetupThiefWidget_Implementation()
{
	ThiefWidget->SetRelativeLocation(WidgetOffset);
	ThiefWidget->SetWidgetSpace(EWidgetSpace::Screen);
	ThiefWidget->SetDrawSize(FVector2D(100.0f, 135.0f));
}

void ASupportDrone::SetupSupporterWidget_Implementation()
{
	// Widget Setup?
	USupporterInteractionWidget* SupporterInteractionWidget = Cast<USupporterInteractionWidget>(SupporterWidget->GetUserWidgetObject());
	if (SupporterInteractionWidget == nullptr)
	{
		UE_LOG(LogClass, Error, TEXT("No Supporter Widget setup on %s"), *GetClass()->GetName());
		return;
	}

	SupporterInteractionWidget->Setup(FunctionClasses, this, CenterImage);
}
/************* Interaction_Interface End **************/