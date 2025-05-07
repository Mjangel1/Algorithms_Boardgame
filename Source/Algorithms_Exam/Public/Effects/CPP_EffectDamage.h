// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effects/CPP_EffectParent.h"

#include "CPP_EffectDamage.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class ALGORITHMS_EXAM_API ACPP_EffectDamage : public ACPP_EffectParent
{
	GENERATED_BODY()

	FTimerHandle DestroyTimer;

public:

	ACPP_EffectDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	int DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UBoxComponent* TriggerBox;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool fromSweep, const FHitResult& result);

	UFUNCTION()
	void DestroyIfNoCollision();
	
};
