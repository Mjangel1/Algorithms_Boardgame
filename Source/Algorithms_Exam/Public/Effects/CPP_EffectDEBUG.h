// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effects/CPP_EffectParent.h"
#include "CPP_EffectDEBUG.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHMS_EXAM_API ACPP_EffectDEBUG : public ACPP_EffectParent
{
	GENERATED_BODY()

	FTimerHandle DestroyTimer;

public:
	// Sets default values for this actor's properties
	ACPP_EffectDEBUG();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	float SecondsUntilDestroy;

	UFUNCTION()
	void DestroyAfterTime();
};
