// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPP_Card.h"
#include "CPP_DiscardPile.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ALGORITHMS_EXAM_API UCPP_DiscardPile : public UObject
{
	GENERATED_BODY()
public:


	TArray<ACPP_Card*> DiscardPileArray;

	UFUNCTION(BlueprintCallable, Category = "DrawPile")
	virtual void AddCardsFromDrawPile(ACPP_Card* Card);

	UFUNCTION(BlueprintCallable, Category = "DrawPile")
	virtual TArray<ACPP_Card*> EmptyDiscardPile();

};
