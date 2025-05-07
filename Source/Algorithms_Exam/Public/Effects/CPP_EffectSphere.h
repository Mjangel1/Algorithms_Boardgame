// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effects/CPP_EffectParent.h"
#include "CPP_Piece.h"
#include "CPP_Sphere_Interface.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "CPP_EffectSphere.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHMS_EXAM_API ACPP_EffectSphere : public ACPP_EffectParent, public ICPP_Sphere_Interface
{
	GENERATED_BODY()

	FTimerHandle DestroySphere;
	
	bool IsInside = false;
	
	int32 Count = 0;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* NiagaraSmoke;

	UPROPERTY()
	UNiagaraComponent* NiagaraComponent;

public:

	ACPP_EffectSphere();

	void BeginPlay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	USphereComponent* TriggerSphere;

	UPROPERTY()
	ACPP_Piece* PieceRef;

	UFUNCTION()
	void DealDamage(ACPP_Piece* PieceInside);

	UFUNCTION()
	void UpdateCountEffect();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool fromSweep, const FHitResult& result);

	virtual void UpdateCount_Implementation() override;

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
	void DestroySphereEffect();
};
