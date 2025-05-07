// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FTeam.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct ALGORITHMS_EXAM_API FTeam
{
public:

	GENERATED_BODY()


	FTeam();
	FTeam(FString SetName, FColor SetColor);
	~FTeam();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	FString TeamName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	FColor TeamColor;
};
