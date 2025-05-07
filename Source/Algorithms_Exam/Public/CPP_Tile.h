// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "F2DVectorInt.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "CPP_Tile.generated.h"

UCLASS()
class ALGORITHMS_EXAM_API ACPP_Tile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Tile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Tile")
	F2DVectorInt TileLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Tile")
	bool bIsOccupied;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	int TeamAffiliation;

	UPROPERTY(BlueprintReadWrite, Category = "Tile")
	AActor* OccupyingActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void DrawTile(const FVector Location, const FVector TileSize);

};
