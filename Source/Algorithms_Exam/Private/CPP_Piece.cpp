// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Piece.h"

#include "CPP_Board.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Framework/Text/SyntaxHighlighterTextLayoutMarshaller.h"
#include "Kismet/GameplayStatics.h"

#include "Player/PlayerComponent.h"
#include "Player/PlayerPawn.h"

// Sets default values
ACPP_Piece::ACPP_Piece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(GetRootComponent());

	/*
	 * Variable Initialization
	 */

	CurrentBoard = Cast<ACPP_Board>(UGameplayStatics::GetActorOfClass(this, ACPP_Board::StaticClass()));

	MaxHealth = Health = 4;
	BoardPosition = F2DVectorInt(-1, -1);
	MovementOptions = TArray<F2DVectorInt>();
	PieceRole = FRole(FTeam("Blue", FColor::Blue), "Warrior");

	DefaultTileColor = FColor(255.f, 255.f, 255.f);
	HighlightedTileColor = FColor(100.f, 255.f, 100.f);
}

// Called when the game starts or when spawned
void ACPP_Piece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Piece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// <summary>
/// Changes the Health of this Piece by the Value inserted. Positive Values will do damage, Negative Values will heal.
/// </summary>
/// <param name="Value"> Damage to deal </param>
/// <returns> Current Health after dealing Damage </returns>
int ACPP_Piece::Damage(int Value)
{
	if (Value > 0)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("damage"));
		if (NiagaraDamage)
		{
		const FVector Location = MeshComponent->GetComponentLocation() + FVector(0,0,60);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraDamage, Location, MeshComponent->GetRelativeRotation());
		}

	}

	if (Value < 0)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Heal"));
		if (NiagaraHeal)
		{
		FVector Location = MeshComponent->GetComponentLocation() + FVector(0, 0, 0);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraHeal, Location, MeshComponent->GetRelativeRotation());
		}
	}

	if ((Health - Value) >= MaxHealth)
	{
		Health = MaxHealth;
	}
	else
	{
		Health -= Value;
		if (Health <= 0)
		{

			DestroyPiece();

		}

	}

	return Health;
}

/// <summary>
/// Tries to move this Piece to another Tile based on the Direction inserted. Will only move if the inserted Direction is a legal move for this Piece, and the target Tile is not occupied.
/// </summary>
/// <param name="TargetPosition"> Where to move this Piece to</param>
/// <returns> Could the Piece move to the desired location </returns>
bool ACPP_Piece::MoveTo(F2DVectorInt TargetPosition)
{

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Moving to position"));
	if (!CurrentBoard)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("!!!WARNING: While moving, this piece has no pointer to the Board!"));
		return false;
	}

	//Verify that the Tile in the CurrentBoard at the BoardPosition location is occupied by this actor
	ACPP_Tile* CurrentTile = CurrentBoard->GetTileAt(BoardPosition);

	if (CurrentTile->OccupyingActor != this)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("!!!WARNING: While moving, this piece's stored location did not coincide with the board!"));
		return false;
	}

	//Verify that the target Tile exists
	ACPP_Tile* TargetTile = CurrentBoard->GetTileAt(TargetPosition);

	if (!TargetTile)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("WARNING: Piece tried to move to a location out of bounds. X %d | Y %d"), TargetPosition.X, TargetPosition.Y));
		return false;
	}

	//Check if target Tile is occupied
	if (TargetTile->bIsOccupied)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("COMMENT: Piece tried to move to X %d | Y %d, but it is already occupied."), TargetPosition.X, TargetPosition.Y));
		return false;
	}

	//Move this Piece from its current location to the target location
	CurrentTile->OccupyingActor = nullptr;
	CurrentTile->bIsOccupied = false;

	auto TargetLocation = TargetTile->GetActorLocation();
	TargetLocation.Z = GetActorLocation().Z;

	SetActorLocation(TargetLocation);

	TargetTile->OccupyingActor = this;
	TargetTile->bIsOccupied = true;
	BoardPosition = TargetPosition;

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Moved to position"));

	return true;
}

int ACPP_Piece::MoveAlongPath(UCPP_AlgorithmPath* Path)
{
	int Cost = CurrentMovementCost;

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Started Moving..."));

	if (Path->Parent)
	{
		if (Path->Parent->Position != BoardPosition) Cost = MoveAlongPath(Path->Parent);
	}

	if (MoveTo(Path->Position))
	{
		Cost += Path->PathCost;
		CurrentMovementCost++;
	}

	return Cost;
}

void ACPP_Piece::DestroyPiece()
{
	APlayerPawn* Player = Cast<APlayerPawn>(GetOwner());
	if (Player != nullptr)
	{
		Player->PlayerComponent->RemoveTotalPieces(this);

		if (auto Tile = CurrentBoard->GetTileAt(BoardPosition))
		{
			Tile->OccupyingActor = nullptr;
			Tile->bIsOccupied = false;
		}

		Destroy();
	}


}

void ACPP_Piece::Onclicked()
{
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("What do you want"));
	
	APlayerPawn* Player = Cast<APlayerPawn>(GetOwner());
	if (Player != nullptr)
	{
		int Points = Player->PlayerComponent->Points;
		int Steps = 0;

		while (Points >= 0)
		{
			if (Points - (CurrentMovementCost + Steps + 1) >= 0)
			{
				Steps++;
				Points -= (CurrentMovementCost + Steps);
			}

			else if (Steps > 100) break;

			else break;
		}

		LegalPaths = Pathfinding->RunPathfinding(BoardPosition, MovementOptions, CurrentBoard, Steps);

		VisualizePathfinding(LegalPaths);

		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%i | %i"), LegalPaths.Num(), Steps));
	}
	
	//Move option appears

	//Attack option appears
	

}

void ACPP_Piece::GetTile(ACPP_Tile* Tile)
{

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Bjorn"));

	for (auto Path : LegalPaths)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Checking Path..."));

		if (Path->Position == Tile->TileLocation)
		{
			//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Starting Movement"));

			APlayerPawn* Player = Cast<APlayerPawn>(GetOwner());

			if (!IsValid(Player)) break;

			Player->PlayerComponent->ActionCost(MoveAlongPath(Path));

			break;
		}
	}
}

void ACPP_Piece::NotHighlightPiece_Implementation()
{


}

void ACPP_Piece::HighlightPiece_Implementation()
{


}

void ACPP_Piece::VisualizePathfinding(TArray<UCPP_AlgorithmPath*> Paths)
{
	//UE_LOG(LogTemp, Log, TEXT("Visualizing..."));

	for (auto Path : Paths)
	{
		auto Tile = CurrentBoard->GetTileAt(Path->Position);

		auto Material = Tile->Mesh->GetMaterial(0);
		auto MaterialInstance = Tile->Mesh->CreateDynamicMaterialInstance(0, Material);

		FColor Color = FColor(HighlightedTileColor);

		if (Path->PathCost > 0) Color = FColor(Color.R / Path->PathCost, Color.G / Path->PathCost, Color.B / Path->PathCost);
		else Color += FColor(25.f, 25.f, 25.f);

		if (MaterialInstance)
		{
			//UE_LOG(LogTemp, Log, TEXT("Valid material"));
			MaterialInstance->SetVectorParameterValue("Color", Color);
		}
	}
}

void ACPP_Piece::ClearVisualizePathfinding()
{
	for (auto Path : LegalPaths)
	{
		auto Tile = CurrentBoard->GetTileAt(Path->Position);

		auto Material = Tile->Mesh->GetMaterial(0);
		auto MaterialInstance = Tile->Mesh->CreateDynamicMaterialInstance(0, Material);

		FColor Color = DefaultTileColor;

		if (MaterialInstance)
		{
			MaterialInstance->SetVectorParameterValue("Color", Color);
		}
	}
}
