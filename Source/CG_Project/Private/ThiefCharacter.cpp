// Fill out your copyright notice in the Description page of Project Settings.

#include "ThiefCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine.h"
#include "InteractionInterface.h"
#include "GameplayPlayerController.h"


// Sets default values
AThiefCharacter::AThiefCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCamera->bUsePawnControlRotation = true;

	// Create the collection sphere
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->SetupAttachment(RootComponent);
	TriggerSphere->SetSphereRadius(200.0f);

	// Bind Begin/End Overlap Functions
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AThiefCharacter::OnComponentBeginOverlap);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &AThiefCharacter::OnComponentEndOverlap);
}

// Called when the game starts or when spawned
void AThiefCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AThiefCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThiefCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AThiefCharacter::AttemptInteraction);

}

void AThiefCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Is Hostile?
	/*if (FGenericTeamId::GetAttitude(OtherActor, this) == ETeamAttitude::Hostile)
	{
		NearHostiles.Add(OtherActor);
		return;
	}*/

	// Can interact with?
	if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		// FString ActorName = OtherActor->GetName();
		// UE_LOG(LogClass, Log, TEXT("Component begins to overlap %s"), *ActorName);

		NearInteractables.AddUnique(OtherActor);
	}
}

void AThiefCharacter::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Is Hostile?
	/*if (FGenericTeamId::GetAttitude(OtherActor, this) == ETeamAttitude::Hostile)
	{
		NearHostiles.Remove(OtherActor);
	}*/

	// Can interact with?
	if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		// FString ActorName = OtherActor->GetName();
		// UE_LOG(LogClass, Log, TEXT("Component ends to overlap %s"), *ActorName);

		NearInteractables.Remove(OtherActor);
	}
}

void AThiefCharacter::PossessedHandler_Implementation(AController* NewController)
{
	// Create Timer to Update Target
	GetWorldTimerManager().SetTimer(UpdateTargetHandle, this, &AThiefCharacter::UpdateTarget, UpdateRate, true, UpdateRate);

	AGameplayPlayerController* GameplayPC = Cast<AGameplayPlayerController>(NewController);
	if (GameplayPC == nullptr)
	{
		return;
	}

	// Set Input Mode
	GameplayPC->bShowMouseCursor = false;
	GameplayPC->SetInputMode(FInputModeGameOnly());
}

void AThiefCharacter::UnpossessedHandler_Implementation(AController* OldController)
{
	// Remove Update Target Timer
	GetWorldTimerManager().ClearTimer(UpdateTargetHandle);
}

void AThiefCharacter::AttemptInteraction()
{
	// Has Target?
	if (CurrentTarget == nullptr)
	{
		UE_LOG(LogClass, Warning, TEXT("No Target to interact with"));
		return;
	}

	// Execute Interaction on Server
	AttemptInteractionExecution(CurrentTarget);
	
	// make shure that no one can interact twice
	UpdateTarget();
}

void AThiefCharacter::AttemptInteractionExecution_Implementation(AActor* Target)
{
	// Call Interact on current Target
	IInteractionInterface::Execute_Interact(Target, this);
}

bool AThiefCharacter::AttemptInteractionExecution_Validate(AActor* Target)
{
	return true;
}

void AThiefCharacter::UpdateTarget_Implementation()
{
	// Calculate new Target
	AActor* NewTarget = CalcBestTarget(NearInteractables);


	// Promote Update
	if (NewTarget != CurrentTarget)
	{
		if (CurrentTarget)
		{
			IInteractionInterface::Execute_ToggleThiefWidget(CurrentTarget, false);
		}

		if (NewTarget)
		{
			IInteractionInterface::Execute_ToggleThiefWidget(NewTarget, true);
		}

		CurrentTarget = NewTarget;

		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Switched Target");
		// UE_LOG(LogClass, Error, TEXT("Switched Target"));
	}

}

AActor* AThiefCharacter::CalcBestTarget(TArray<AActor*> Actors)
{
	AActor* BestTarget = nullptr;
	float BestDotProduct = -1;

	for (AActor* Actor : Actors)
	{
		// Allowed to interact with?
		if (!IInteractionInterface::Execute_CanInteract(Actor, this)) 
		{
			continue;
		}

		// Get Vector to Interactable
		FVector ActorLocation = IInteractionInterface::Execute_GetInteractionLocation(Actor);
		FVector CameraLocation = FirstPersonCamera->GetComponentLocation();
		FVector ToActor = ActorLocation - CameraLocation;
		ToActor.Normalize();

		// Get Camera Forward
		FVector CamForward = FirstPersonCamera->GetForwardVector();

		// Calculate Dot Product between CamForward and toInteractable
		float DotProduct = FVector::DotProduct(ToActor, CamForward);

		// check if best
		if (DotProduct > BestDotProduct)
		{
			BestTarget = Actor;
			BestDotProduct = DotProduct;
		}
	}

	if (BestDotProduct > InteractionDotThreshold)
	{
		// UE_LOG(LogClass, Log, TEXT("%s is chosen Target to Interact with"), *BestInteractable->GetName());
		return BestTarget;
	}

	return nullptr;
}