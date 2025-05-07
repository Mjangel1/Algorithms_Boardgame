// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "F2DVectorInt.h"

#include "CPP_AlgorithmPath.generated.h"

class ACPP_Tile;
/**
 * 
 */
UCLASS(Blueprintable)
class ALGORITHMS_EXAM_API UCPP_AlgorithmPath : public UObject
{
	GENERATED_BODY()

public:

	UCPP_AlgorithmPath();
	UCPP_AlgorithmPath(F2DVectorInt SetPosition);
	UCPP_AlgorithmPath(F2DVectorInt SetPosition, int SetPathCost, UCPP_AlgorithmPath* SetParent);

	/*
	 * Variables
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Algorithm Path")
	F2DVectorInt Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Algorithm Path")
	int PathCost;

	UPROPERTY()
	UCPP_AlgorithmPath* Parent;

};