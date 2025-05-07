// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPP_Card.h"
#include "CPP_CountingSort.generated.h"


UCLASS(BlueprintType, Blueprintable)
class ALGORITHMS_EXAM_API UCPP_CountingSort : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CountingSort")
	TArray<ACPP_Card*> Sort(TArray<ACPP_Card*> CardsForSorting);


};
