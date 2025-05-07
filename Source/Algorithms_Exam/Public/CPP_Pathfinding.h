

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "F2DVectorInt.h"

#include "CPP_Pathfinding.generated.h"

class UCPP_AlgorithmPath;
class ACPP_Board;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ALGORITHMS_EXAM_API ACPP_Pathfinding : public AActor
{
private:

	GENERATED_BODY()

public:

	ACPP_Pathfinding();

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	TArray<UCPP_AlgorithmPath*> RunPathfinding(F2DVectorInt StartPosition, TArray<F2DVectorInt> MovementOptions, ACPP_Board* Board, int Steps = 3);
};
