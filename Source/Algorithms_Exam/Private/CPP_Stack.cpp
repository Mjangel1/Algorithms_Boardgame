// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Stack.h"

#include "CPP_Board.h"
#include "CPP_DiscardPile.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Algo/RandomShuffle.h"



void UCPP_Stack::Push_Implementation(ACPP_Card* Card)
{
	if (!Card) return;
	CardsArray.Emplace(Card); //adds new card object to the end (on top)

}

ACPP_Card* UCPP_Stack::Pop_Implementation()
{
	ACPP_Card* ClassRef = nullptr;
	if (CardsArray.IsEmpty())
	{
		auto Cards = DiscardPile->EmptyDiscardPile();

		for (auto Card : Cards)
		{
			Push_Implementation(Card);
		}
	}

	if (!CardsArray.IsEmpty())
	{
		ClassRef = CardsArray.Last();
		CardsArray.Pop();
		
	}
	return ClassRef; // ClassRef can be used to add the popped card to the hand or other card stock
}

void UCPP_Stack::CreateDiscardPile()
{
	if (!DiscardPile) DiscardPile = NewObject<UCPP_DiscardPile>();
}

void UCPP_Stack::InitializeStack(FVector Location)
{
	if (InitCardsClasses.IsEmpty()) return;

	for (int i = 0; i < InitCardsClasses.Num(); i++)
	{
		FActorSpawnParameters SpawnParameters;

		AActor* InitCardActor = GetWorld()->SpawnActor(InitCardsClasses[i]);

		ACPP_Card* InitCard = Cast<ACPP_Card>(InitCardActor);

		if (InitCard)
		{
			Push_Implementation(InitCard);

			Location += FVector(0.f, 0.f, InitCard->Mesh->GetRelativeScale3D().Z + 10.f);

			InitCard->SetActorLocation(Location);
		}
	}

	Algo::RandomShuffle(CardsArray);

	//UE_LOG(LogTemp, Log, TEXT("Filled the CardsArray %i"), InitCardsClasses.Num());
}
