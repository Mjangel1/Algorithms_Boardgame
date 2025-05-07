// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerComponent.h"

#include "CPP_Card.h"
#include "Blueprint/UserWidget.h"
#include "GameMode/BoardersGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerComponent::UPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	MaxPoints = 0;
	CurrentPoints = 0;

}


// Called when the game starts
void UPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	RefillPoints();
}


// Called every frame
void UPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	/*for (int32 i = 0; i < SpawnedPieces.Num(); i++)
	{

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%s"), *SpawnedPieces[i]->GetName()));

	}*/
	

}



void UPlayerComponent::RemoveTotalPieces(ACPP_Piece* RemovePiece)
{
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%p"),RemovePiece));
	
	SpawnedPieces.Remove(RemovePiece);
	if (SpawnedPieces.Num()==0)
	{
		ABoardersGameMode* GameMode= Cast<ABoardersGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->EndGame_Implementation();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%d"), SpawnedPieces.Num()));

}

bool UPlayerComponent::PieceBelongToPlayer(ACPP_Piece* InteractPiece)
{
	
	for (ACPP_Piece* Piece : SpawnedPieces)
	{
		if (Piece == InteractPiece)
		{
			
			return true;
		}


	}

	return false;
}

void UPlayerComponent::ActionCost(int32 Cost)
{
	int32 NewCost = Cost;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Called"));
	//Logic for taking points away points from player when he does an action
	if (Points >= Cost)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Cost lower then points"));
		if (Points >= 0)
		{
			Points = CurrentPoints - Cost;

			CurrentPoints = Points;

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%d"), CurrentPoints));

		}
		
	}


}

void UPlayerComponent::FillArray(ACPP_Piece* Piece)
{
	
	SpawnedPieces.Emplace(Piece);

}


void UPlayerComponent::RefillPoints()
{
	
	Points = MaxPoints;
	CurrentPoints = MaxPoints;

}

TArray<int> UPlayerComponent::GetCardIndexOfRole(FString RoleName)
{
	TArray<int> CardIndexes;

	if (!Hand) return CardIndexes;

	for (int i = 0; i < Hand->Cards.Num(); i++)
	{
		if (!Hand->Cards[i]) continue;

		if (Hand->Cards[i]->CardRole.RoleName == RoleName)
		{
			CardIndexes.Add(i);
		}
	}

	return CardIndexes;
}






