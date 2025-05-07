// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 
#include "CPP_DiscardPile.h"
#include "CPP_Stacks_Interface.h"
#include "UObject/NoExportTypes.h"
#include "CPP_Stack.generated.h"

class UCPP_DiscardPile;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ALGORITHMS_EXAM_API UCPP_Stack : public UObject, public ICPP_Stacks_Interface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Stack")
	virtual void Push_Implementation(ACPP_Card* Card) override;

	UFUNCTION(BlueprintCallable, Category = "Stack")
	virtual ACPP_Card* Pop_Implementation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stack")
	TArray<ACPP_Card*> CardsArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stack")
	TArray<TSubclassOf<ACPP_Card>> InitCardsClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stack")
	FRole Role;

	UPROPERTY()
	UCPP_DiscardPile* DiscardPile;

	UFUNCTION(BlueprintCallable)
	void CreateDiscardPile();

	UFUNCTION(BlueprintCallable)
	void InitializeStack(FVector Location);
	
};
