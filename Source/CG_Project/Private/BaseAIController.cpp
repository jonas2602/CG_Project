// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAIController.h"


ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// UE_LOG(LogClass, Warning, TEXT("Try to Get Team Attitude Towards %s"), *Other.GetName());

	ETeamAttitude::Type Attitude;
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
	if (OtherTeamAgent)
	{
		Attitude = FGenericTeamId::GetAttitude(GetGenericTeamId(), OtherTeamAgent->GetGenericTeamId());
	}
	else
	{
		UE_LOG(LogClass, Error, TEXT("%s is no TeamAgent"), *Other.GetName());
		Attitude = ETeamAttitude::Neutral;
	}

	/*FString AttitudeString;
	switch (Attitude)
	{
		case ETeamAttitude::Friendly: { AttitudeString = "Friendly"; break; }
		case ETeamAttitude::Neutral: { AttitudeString = "Neutral"; break; }
		case ETeamAttitude::Hostile: { AttitudeString = "Hostile"; break; }
		default: { AttitudeString = "Failed"; break; }
	}

	UE_LOG(LogClass, Warning, TEXT("Attitude from %s Towards %s is %s"),*GetPawn()->GetName(), *Other.GetName(), *AttitudeString);*/

	return Attitude;
}

void ABaseAIController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	IGenericTeamAgentInterface* ControlledAgent = Cast<IGenericTeamAgentInterface>(GetPawn());
	if (ControlledAgent)
	{
		ControlledAgent->SetGenericTeamId(NewTeamID);
	}
}


FGenericTeamId ABaseAIController::GetGenericTeamId() const
{
	const IGenericTeamAgentInterface* ControlledAgent = Cast<const IGenericTeamAgentInterface>(GetPawn());
	if (ControlledAgent)
	{
		return ControlledAgent->GetGenericTeamId();
	}

	return FGenericTeamId();
}

