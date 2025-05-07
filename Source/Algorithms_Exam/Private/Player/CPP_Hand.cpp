// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPP_Hand.h"

#include "CPP_Card.h"
#include "CPP_CountingSort.h"
#include "CPP_Stack.h"
#include "F2DVectorInt.h"
#include "CPP_Piece.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerComponent.h"

void UCPP_Hand::DrawCard(UCPP_Stack* Stack)
{
	if (!Stack)
	{
		return;
	}

	if (!Cards.Contains(nullptr) && Cards.Num() >= MaxCards)
	{
		return;
	}

	Cards.Add(Stack->Pop_Implementation());
}

ACPP_Card* UCPP_Hand::UseCard(int Index, F2DVectorInt PieceLocation, bool bInvertCardDirection, UPlayerComponent* PlayerComponent)
{
	if (Index < 0 || Index >= Cards.Num() || !PlayerComponent) return nullptr;

	ACPP_Card* TargetCard = Cards[Index];

	if (!TargetCard) return nullptr;

	if (TargetCard->CardCost > PlayerComponent->Points)
	{
		return nullptr;
	}

	Cards.RemoveAt(Index, 1, true);

	PlayerComponent->Points -= TargetCard->CardCost;

	for (auto Pile : DrawPiles)
	{
		if (Pile->Role.ClassIndex == TargetCard->CardRole.ClassIndex)
		{
			DrawCard(Pile);

			if (!Pile->DiscardPile) Pile->CreateDiscardPile();

			TargetCard->SpawnEffects(TargetCard->FindCardEffectLocations(PieceLocation, bInvertCardDirection));

			TargetCard->RemoveVisualizeEffects();

			Pile->DiscardPile->AddCardsFromDrawPile(TargetCard);

			break;
		}
	}

	return TargetCard;
}

void UCPP_Hand::InitializeDrawPile(ACPP_Piece* Piece, FVector Location)
{
	for (auto Class : DrawPileClasses)
	{
		if (Class->GetDefaultObject<UCPP_Stack>()->Role.RoleName == Piece->PieceRole.RoleName)
		{
			auto DrawPile = NewObject<UCPP_Stack>(this, Class);
			DrawPile->Role = Piece->PieceRole;
			DrawPile->InitializeStack(Location);
			DrawPile->CreateDiscardPile();

			DrawPiles.Emplace(DrawPile);

			DrawCard(DrawPile);
			DrawCard(DrawPile);

			return;
		}
	}

	auto DrawPile = NewObject<UCPP_Stack>();
	DrawPile->Role = Piece->PieceRole;
	DrawPile->InitializeStack(Location);
	DrawPile->CreateDiscardPile();

	DrawPiles.Emplace(DrawPile);

	DrawCard(DrawPile);
	DrawCard(DrawPile);
}
