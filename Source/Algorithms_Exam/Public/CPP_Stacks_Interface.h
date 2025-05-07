// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_Card.h"
#include "CPP_Stacks_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPP_Stacks_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ALGORITHMS_EXAM_API ICPP_Stacks_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "StacksInterface")
	void Push(ACPP_Card* Card);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "StacksInterface")
	ACPP_Card* Pop();
};
