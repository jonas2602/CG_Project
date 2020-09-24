// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Private/PawnInterface.h"
#include "ThiefCharacter.generated.h"

UCLASS(BlueprintType)
class CG_PROJECT_API AThiefCharacter : public ABaseCharacter // , public IPawnInterface
{
	GENERATED_BODY()

	/** Collection sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* TriggerSphere;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCamera;

public:
	// Sets default values for this character's properties
	AThiefCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

/************ Pawn Interface Start *************/
public:
	// virtual void Init_Implementation(AController* NewController) override;
	// virtual void Deinit_Implementation(AController* OldController) override;
/************* Pawn Interface End **************/

protected:	
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Interaction")
	void PossessedHandler(AController* NewController);
	void PossessedHandler_Implementation(AController* NewController);
	
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Interaction")
	void UnpossessedHandler(AController* OldController);
	void UnpossessedHandler_Implementation(AController* OldController);

protected:
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void AttemptInteraction();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Interaction")
	void AttemptInteractionExecution(AActor* Target);

	// Returns Target if InteractionTarget, returns nullptr if CombatTarget or no target
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void UpdateTarget();
	virtual void UpdateTarget_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	AActor* CalcBestTarget(TArray<AActor*> Actors);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction")
	TArray<AActor*> NearInteractables;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	float InteractionDotThreshold = 0.85f;

	// Rate to recalcutate the target
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	float UpdateRate = 0.2f;

	FTimerHandle UpdateTargetHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction")
	AActor* CurrentTarget;
};
