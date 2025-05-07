// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRole.h"
#include "F2DVectorInt.h"

#include "CPP_Card.generated.h"

class ACPP_Board;
class ACPP_EffectParent;

UCLASS(BlueprintType,Blueprintable)
class ALGORITHMS_EXAM_API ACPP_Card : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AActor*> VisualizedEffectsArray;

public:	
	// Sets default values for this actor's properties
	ACPP_Card();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	int32 CardCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FRole CardRole;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<TSubclassOf<ACPP_EffectParent>> CardEffects; //An array containing which type of attack is used

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "Card")
	TSubclassOf<AActor> EffectVisualActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ACPP_Board* Board;

	UFUNCTION(BlueprintCallable, Category = "Card")
	void SpawnEffects(TArray<FVector> EffectLocations);  //FTile instead of location?

	UFUNCTION(BlueprintCallable, Category = "Card")
	void VisualizeEffects(TArray<FVector> EffectLocations);

	UFUNCTION(BlueprintCallable, Category = "Card")
	void RemoveVisualizeEffects();

	UFUNCTION(BlueprintCallable, Category = "Card")
	TArray<FVector> FindCardEffectLocations(F2DVectorInt PieceLocation, bool bInvertDirection);

};
