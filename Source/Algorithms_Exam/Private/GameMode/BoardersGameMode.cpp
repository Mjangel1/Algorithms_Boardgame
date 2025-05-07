// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BoardersGameMode.h"

#include "EndGameWidget.h"
#include "Player/PlayerPawn.h"
//#include "UIComponent.h"
#include "Blueprint/UserWidget.h"
#include "Effects/CPP_Sphere_Interface.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerComponent.h"

ABoardersGameMode::ABoardersGameMode()
{

	Player1Class = APlayerPawn::StaticClass();
	Player2Class = APlayerPawn::StaticClass();

	CurrentPlayer = nullptr;
	Player1 = nullptr;
	Player2 = nullptr;

}

void ABoardersGameMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	SpawnPlayers();
	

	CurrentPlayer = PlayerArray[0];
	if (PlayerController != nullptr)
	{
		SwitchPlayer();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Player1"));
		
	}

	
}


void ABoardersGameMode::Enqueue_Implementation(APawn* Actor)
{
	PlayerArray.Emplace(Actor);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Player Enqueued"));
}

APawn* ABoardersGameMode::Dequeue_Implementation()
{
	APawn* DequeueActor = nullptr;

	//check if the array is not empty
	if (!PlayerArray.IsEmpty())
	{
		//assigns  DequeueActor to be the player in the index 0 of the array and remove it
		DequeueActor = PlayerArray[0];
		PlayerArray.RemoveAt(0);

	}
	//returns the DequeuedPlayer
	return DequeueActor;
}


void ABoardersGameMode::SpawnPlayers()
{
	//spawns players at a give location in the world and places them into the queue
	const FRotator Rotation = FRotator(0.0,90.0,0.0);
	const FRotator Rotation2 = FRotator(0.0,-90.0,0.0f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	Player1 = GetWorld()->SpawnActor<APlayerPawn>(Player1Class, PLayer1SpawnLocation(), Rotation, SpawnParameters);
	Player2 = GetWorld()->SpawnActor<APlayerPawn>(Player2Class, PLayer2SpawnLocation(), Rotation2, SpawnParameters);

	Enqueue_Implementation(Player1);

	Enqueue_Implementation(Player2);

}

void ABoardersGameMode::EndTurn_Implementation()
{
	
	
	if (PlayerArray.Num() == 0)
	{
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Empty"));
		}*/
		return;
	}

	//check is the player is valid
	if (IsValid(CurrentPlayer))
	{
		auto PlayerPawn = Cast<APlayerPawn>(CurrentPlayer);
		if (PlayerPawn)
		{
			// clean the pathfinding
			auto Piece = PlayerPawn->SavedPiece;

			if (Piece)
			{
				Piece->ClearVisualizePathfinding();
			}

			PlayerPawn->Deselect();
		}
		//UnPossesses the current player
		CurrentPlayer->UnPossessed();

		ResetPlayer(CurrentPlayer);
	}


	// calls dequeue first and get the pawn return, then call enqueue
	APawn* PlayerDequeued = Dequeue_Implementation();

	if (PlayerDequeued)
	{
		
		//Enqueue the Player that was removed from the que back into it
		Enqueue_Implementation(PlayerDequeued);

	}


	
	if (!PlayerArray.IsEmpty())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Assigned"));
		//Assigns Current Player to be the next player in the queue
		CurrentPlayer = PlayerArray[0];

		if (IsValid(CurrentPlayer) && IsValid(PlayerController))
		{
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ABoardersGameMode::SwitchPlayer);

		}
	}
}

void ABoardersGameMode::SwitchPlayer()
{
	//Possesses the new Player and Set the correct widget corresponding to the active Player
	PlayerController->Possess(CurrentPlayer);
	if (CurrentPlayer == Player1)
	{
		Player1WidgetSwitch();
	}
	else if (CurrentPlayer == Player2)
	{
		Player2WidgetSwitch();
	}

	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *CurrentPlayer->GetName()));

	//find existing spheres
	if(EffectSphereRef == nullptr)  
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), EffectSphereClass, FoundActors);
		
	}
	 //if sphere/s exist, we run long term damage for each
	for (int i= 0; i < FoundActors.Num(); i++)
	{
		//check for every sphere present in game and call out the function UpdateCount in each sphere present in the world
		ICPP_Sphere_Interface::Execute_UpdateCount(FoundActors[i]);
	}
}

void ABoardersGameMode::ResetPlayer(APawn* Player)
{
	if (Player == Player1)
	{

		//logic to place player back to the starting position
		//reset points so player can use his points again

		Player->SetActorLocation(PLayer1SpawnLocation());

		UPlayerComponent* PlayerComponent = Player->FindComponentByClass<UPlayerComponent>();
		if (IsValid(PlayerComponent))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Update Points"));
			PlayerComponent->RefillPoints();

			for (auto Piece : PlayerComponent->SpawnedPieces)
			{
				Piece->CurrentMovementCost = 0;
			}
		}			

	}
	if (Player == Player2)
	{
		

		Player->SetActorLocation(PLayer2SpawnLocation());
		UPlayerComponent* PlayerComponent = Player->FindComponentByClass<UPlayerComponent>();
		if (IsValid(PlayerComponent))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Update Points"));
			PlayerComponent->RefillPoints();

			for (auto Piece : PlayerComponent->SpawnedPieces)
			{
				Piece->CurrentMovementCost = 0;
			}			
		}

	}

}

void ABoardersGameMode::Player1WidgetSwitch_Implementation()
{
}


void ABoardersGameMode::Player2WidgetSwitch_Implementation()
{
}

FVector ABoardersGameMode::PLayer1SpawnLocation()
{
	const AActor* SpawnPoint1 = UGameplayStatics::GetActorOfClass(GetWorld(), Player1SpawnPoint);
	const FVector Player1Location = SpawnPoint1->GetActorLocation();


	return Player1Location;
}

FVector ABoardersGameMode::PLayer2SpawnLocation()
{
	const AActor* SpawnPoint2 = UGameplayStatics::GetActorOfClass(GetWorld(), Player2SpawnPoint);
	const FVector Player2Location = SpawnPoint2->GetActorLocation();
	return Player2Location;

}



UUserWidget* ABoardersGameMode::CreateUIWidget(TSubclassOf<UEndGameWidget> WidgetClass)
{
	if (WidgetClass) {
		UIInstance = CreateWidget<UEndGameWidget>(GetWorld(), WidgetClass);
		if (UIInstance) {
			UIInstance->AddToViewport();
		}
	}
	return UIInstance;
}


void ABoardersGameMode::EndGame_Implementation()
{
	//Find the player component for each player
	UPlayerComponent* Player1Component = Player1->FindComponentByClass<UPlayerComponent>();
	UPlayerComponent* Player2Component = Player2->FindComponentByClass<UPlayerComponent>();

	//Compares the size of the array SpawnPieces in each player to determine the winner or if it is a tie.
	if (Player1Component->SpawnedPieces.Num() >= 0 && Player2Component->SpawnedPieces.Num() > Player1Component->SpawnedPieces.Num())
	{
		CreateUIWidget(UEndGameWidgetClass);
		if (UEndGameWidgetClass)
		{
			UIInstance->Text->SetText(FText::FromString(TEXT("Player2 wins!")));
		}
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Game Player 2 wins"));
		}*/
		

	}
	if (Player2Component->SpawnedPieces.Num() >= 0 && Player1Component->SpawnedPieces.Num() > Player2Component->SpawnedPieces.Num())
	{
		CreateUIWidget(UEndGameWidgetClass);
		if(UEndGameWidgetClass)
		{
			UIInstance->Text->SetText(FText::FromString(TEXT("Player1 wins!")));
		}
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Game Player 1 wins"));
		}*/
		
	}
	if (Player2Component->SpawnedPieces.Num() >= 0 && Player1Component->SpawnedPieces.Num() >= 0 && Player1Component->SpawnedPieces.Num() == Player2Component->SpawnedPieces.Num())
	{
		CreateUIWidget(UEndGameWidgetClass);
		if (UEndGameWidgetClass)
		{
			UIInstance->Text->SetText(FText::FromString(TEXT("Tie!, How Is This Possible")));
		}

		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tie"));
		}*/
		
	}

}



