// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "F2DVectorInt.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct ALGORITHMS_EXAM_API F2DVectorInt
{
public:

	GENERATED_BODY()

	F2DVectorInt();
	F2DVectorInt(const int SetX, const int SetY);

	~F2DVectorInt();

	bool WithinRange(const F2DVectorInt& Min, const F2DVectorInt& Max) const;
	bool WithinRange(const F2DVectorInt& Max) const;

	/*
	 * Operator Overloading
	 */

	F2DVectorInt operator+(const F2DVectorInt& Other) const;
	F2DVectorInt operator-(const F2DVectorInt& Other) const;
	bool operator==(const F2DVectorInt& Other) const;

	/*
	 * Variables
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Vector Int")
	int X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Vector Int")
	int Y;
};
