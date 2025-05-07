// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Card.h"

#include "Effects/CPP_EffectLocation.h"
#include "Effects/CPP_EffectParent.h"
#include "CPP_Board.h"
#include "Effects/CPP_EffectDamage.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPP_Card::ACPP_Card()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CardCost = 0;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Mesh->SetupAttachment(GetRootComponent());

	CardEffects.Init(nullptr, 9);
}

// Called when the game starts or when spawned
void ACPP_Card::BeginPlay()
{
	Super::BeginPlay();

	Board = Cast<ACPP_Board>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPP_Board::StaticClass()));
	
}

// Called every frame
void ACPP_Card::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FVector> ACPP_Card::FindCardEffectLocations(F2DVectorInt PieceLocation, bool bInvertDirection)
{
	TArray<FVector> EffectLocations;

	if (!Board) return EffectLocations;

	F2DVectorInt StartLocation(0, 0);

	int Modulo = static_cast<int>(sqrt(CardEffects.Num()));

	//Finds the EffectLocation Class type, and saves the index as start location
	for (int i = 0; i < CardEffects.Num(); i++)
	{
		if (CardEffects[i] == ACPP_EffectLocation::StaticClass())
		{
			StartLocation = F2DVectorInt(i % Modulo, static_cast<int>(floor(i / Modulo)));
			break;
		}
	}

	//Spawns all Card Effects on the matching Tile location
	for (int i = 0; i < CardEffects.Num(); i++)
	{
		UClass* EffectClass = CardEffects[i];

		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT(""), SpawnPosition.X, SpawnPosition.Y));

		//TODO: Logic for where to spawn the effects does not work properly

		F2DVectorInt SpawnPosition = F2DVectorInt((i % Modulo), static_cast<int>(floor(i / Modulo)))
			- StartLocation + PieceLocation;

		if (bInvertDirection)
		{
			SpawnPosition = F2DVectorInt(-(i % Modulo), -static_cast<int>(floor(i / Modulo)))
				+ StartLocation + PieceLocation;

		}

		ACPP_Tile* SpawnTile = Board->GetTileAt(SpawnPosition);

		if (!SpawnTile)
		{
			EffectLocations.Emplace(FVector(INFINITY));

			continue;
		}

		EffectLocations.Emplace(Board->GetTileAt(SpawnPosition)->GetActorLocation());
	}

	return EffectLocations;
}

/// Activates the card, and does all its effects
/// @param PieceLocation Where the piece using the card is located on the board
///	@param bInvertDirection Whether to invert the placement of the effects. Needed when it is Player1's turn
void ACPP_Card::SpawnEffects(TArray<FVector> EffectLocations)
{
	if (!Board || EffectLocations.IsEmpty()) return;

	for (int i = 0; i < EffectLocations.Num(); i++)
	{
		if (i >= CardEffects.Num()) return;

		if (CardEffects[i] == nullptr || CardEffects[i]->StaticClass() == ACPP_EffectLocation::StaticClass() || EffectLocations[i].Size() >= FVector(INFINITY - 1).Size()) continue;

		GetWorld()->SpawnActor(CardEffects[i], &EffectLocations[i]);
	}
}

void ACPP_Card::VisualizeEffects(TArray<FVector> EffectLocations)
{
	if (!Board || EffectLocations.IsEmpty()) return;

	RemoveVisualizeEffects();

	for (int i = 0; i < EffectLocations.Num(); i++)
	{
		if (i >= CardEffects.Num()) return;

		if (CardEffects[i] == nullptr || CardEffects[i]->StaticClass() == ACPP_EffectLocation::StaticClass() || EffectLocations[i].Size() >= FVector(INFINITY - 1).Size()) continue;

		//UE_LOG(LogTemp, Log, TEXT("%p"), CardEffects[i]->StaticClass());

		VisualizedEffectsArray.Emplace(GetWorld()->SpawnActor(EffectVisualActor, &EffectLocations[i]));
	}
}

void ACPP_Card::RemoveVisualizeEffects()
{
	//UE_LOG(LogTemp, Log, TEXT("Removing Visuals"))

	for (int i = 0; i < VisualizedEffectsArray.Num(); i++)
	{
		auto Visual = VisualizedEffectsArray[i];

		if (Visual) Visual->Destroy();

		//UE_LOG(LogTemp, Log, TEXT("Removed Visual %i"), i);
	}

	VisualizedEffectsArray.Empty();
}
