// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPP_Tile.h"

#include "FTileArray.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHMS_EXAM_API UFTileArray : public UObject
{
	GENERATED_BODY()

public:

	UFTileArray();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Array")
	TArray<ACPP_Tile*> TileArray;
	
};
