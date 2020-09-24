// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInfo.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemInfo
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemInfo")
		FString ItemName;

		//check to see if the aggro record matches another aggro record by overloading the "==" operator.
		FORCEINLINE bool operator==(const FItemInfo &Other) const
		{
			return ItemName.Compare(Other.ItemName) == 0;
		}
};


/*UCLASS()
class CG_PROJECT_API UItemInfo : public UObject
{
	GENERATED_BODY()
	
	
	
	
};*/
