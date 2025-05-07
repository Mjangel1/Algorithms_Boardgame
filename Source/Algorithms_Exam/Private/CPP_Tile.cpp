// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Tile.h"

// Sets default values
ACPP_Tile::ACPP_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsOccupied = false;
	TeamAffiliation = 0;
	OccupyingActor = nullptr;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
}

// Called when the game starts or when spawned
void ACPP_Tile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Tile::DrawTile(const FVector Location, const FVector TileSize)
{
	SetActorLocation(Location);
	Mesh->SetWorldScale3D(TileSize/100);
}
