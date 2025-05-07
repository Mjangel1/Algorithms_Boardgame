// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_EffectParent.generated.h"

enum EEffectType
{
	UNDEFINED,
	LOCATION,
	DAMAGE
};

UCLASS()
class ALGORITHMS_EXAM_API ACPP_EffectParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_EffectParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EEffectType EffectType = UNDEFINED;

};
