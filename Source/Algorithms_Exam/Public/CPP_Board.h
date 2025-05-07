// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "FTileArray.h"
#include "F2DVectorInt.h"

#include "CPP_Board.generated.h"

UCLASS()
class ALGORITHMS_EXAM_API ACPP_Board : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UFTileArray*> TileArray2D;
	
public:	
	// Sets default values for this actor's properties
	ACPP_Board();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	F2DVectorInt InitBoardSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	int TeamAffiliationRowCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	FVector TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	float InitBoardPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	float InitBoardMargin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	float InitBoardDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	TSubclassOf<ACPP_Tile> TileActor;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Board")
	bool SetBoardSize(const F2DVectorInt Size);

	UFUNCTION(BlueprintCallable, Category = "Board")
	bool SetBoardTeamAffiliation(const int TeamRowCount);

	UFUNCTION(BlueprintCallable, Category = "Board")
	ACPP_Tile* GetTileAt(const int X, const int Y);
	ACPP_Tile* GetTileAt(F2DVectorInt Position);

	UFUNCTION(BlueprintCallable, Category = "Board")
	F2DVectorInt GetBoardSize();

	UFUNCTION(BlueprintCallable, Category = "Board")
	void DrawBoard(const FVector BoardLocation, const FVector TilesSize, const float BackgroundDepth, const float Padding, const float Margin);
};