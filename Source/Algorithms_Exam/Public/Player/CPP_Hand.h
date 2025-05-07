// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPP_Hand.generated.h"

class UPlayerComponent;
struct FRole;
struct F2DVectorInt;
class UCPP_Stack;
class UCPP_CountingSort;
class ACPP_Card;
class ACPP_Piece;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ALGORITHMS_EXAM_API UCPP_Hand : public UObject
{
	GENERATED_BODY()

	void DrawCard(UCPP_Stack* Stack);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hand")
	int MaxCards = 8;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hand")
	TArray<ACPP_Card*> Cards;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Draw Piles")
	TArray<UCPP_Stack*> DrawPiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draw Piles")
	TArray<TSubclassOf<UCPP_Stack>> DrawPileClasses;

	UPROPERTY()
	UCPP_CountingSort* Sorter;

	UFUNCTION(BlueprintCallable, Category = "Hand")
	ACPP_Card* UseCard(int Index, F2DVectorInt PieceLocation, bool bInvertCardDirection, UPlayerComponent* PlayerComponent);

	UFUNCTION()
	void InitializeDrawPile(ACPP_Piece* Piece, FVector Location);
};
