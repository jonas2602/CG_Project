// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableBase.h"
#include "InteractionWidget.h"
#include "SupporterInteractionWidget.h"
#include "GameplayGameState.h"
#include "FunctionWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
AInteractableBase::AInteractableBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	// Create Root Component
	RootBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Root"));
	SetRootComponent(RootBillboard);

	// Create the static mesh component
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableMesh"));
	InteractableMesh->SetupAttachment(RootComponent);

	// Create the Interaction Widget components
	ThiefWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ThiefWidget"));
	ThiefWidget->SetupAttachment(RootComponent);
	SupporterWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SupporterWidget"));
	SupporterWidget->SetupAttachment(RootComponent);

	// Setup Interaction Widget
	IInteractionInterface::Execute_SetupThiefWidget(this);
}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	// Setup Interaction-things
	IInteractionInterface::Execute_SetupThiefWidgetText(this, WidgetDescription);
	IInteractionInterface::Execute_ToggleThiefWidget(this, false);

	IInteractionInterface::Execute_SetupSupporterWidget(this);
	IInteractionInterface::Execute_ToggleSupporterWidget(this, false);
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*void AInteractableBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInteractableBase, CanInteract);
}*/

/************ Interaction_Interface Start *************/
void AInteractableBase::Interact_Implementation(AActor* Interactor)
{
	UE_LOG(LogClass, Warning, TEXT("%s starts interacting with %s"), *Interactor->GetName(), *GetName());
}

void AInteractableBase::ToggleThiefWidget_Implementation(bool Highlight)
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

void AInteractableBase::ToggleSupporterWidget_Implementation(bool Highlight)
{
	// Widget Setup?
	USupporterInteractionWidget* SupporterInteractionWidget = Cast<USupporterInteractionWidget>(SupporterWidget->GetUserWidgetObject());
	if (SupporterInteractionWidget == nullptr)
	{
		UE_LOG(LogClass, Error, TEXT("No Supporter Widget setup on %s"), *GetClass()->GetName());
		return;
	}

	// Is allowed to see Supporter Widget?
	if (SupporterWidget)
	{
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

FVector AInteractableBase::GetInteractionLocation_Implementation()
{
	return ThiefWidget->GetComponentLocation();
}

bool AInteractableBase::CanInteract_Implementation(AActor* Interactor)
{
	return CanInteract;
}

void AInteractableBase::SetupThiefWidgetText_Implementation(const FText& Text)
{
	// Get Widget from Component
	UUserWidget* WidgetBP = ThiefWidget->GetUserWidgetObject();
	if (WidgetBP)
	{
		// Cast to ParentClass
		UInteractionWidget* Widget = Cast<UInteractionWidget>(WidgetBP);
		if (Widget)
		{
			// Setup Text
			Widget->SetInteractionText(Text);
			// UE_LOG(LogClass, Log, TEXT("InteractionWidget TextSetup successful"));
		}
		else
		{
			UE_LOG(LogClass, Log, TEXT("Widget is no InteractionWidget"));
		}
	}
	else
	{
		UE_LOG(LogClass, Log, TEXT("InteractWidget missing"));
	}
}

void AInteractableBase::SetupThiefWidget_Implementation()
{
	ThiefWidget->SetRelativeLocation(WidgetOffset);
	ThiefWidget->SetWidgetSpace(EWidgetSpace::Screen);
	ThiefWidget->SetDrawSize(FVector2D(100.0f, 135.0f));
}

void AInteractableBase::SetupSupporterWidget_Implementation()
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