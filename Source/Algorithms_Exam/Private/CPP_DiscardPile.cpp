// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DiscardPile.h"

void UCPP_DiscardPile::AddCardsFromDrawPile(ACPP_Card* Card)
{
	if (!Card) return;
	DiscardPileArray.Add(Card);
	
	//shuffle
	for (int32 i = DiscardPileArray.Num() - 1; i > 0; i--)
	{
		int32 SwapingIndex = FMath::RandRange(0, i);
		DiscardPileArray.Swap(i, SwapingIndex);
	}
}

TArray<ACPP_Card*> UCPP_DiscardPile::EmptyDiscardPile()
{
	auto Cards = DiscardPileArray;

	DiscardPileArray.Empty();

	return Cards;
}
