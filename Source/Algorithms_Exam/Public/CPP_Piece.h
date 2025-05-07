// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_AlgorithmPath.h"
#include "CPP_Pathfinding.h"
#include "CPP_Tile.h"
#include "GameFramework/Actor.h"
#include "F2DVectorInt.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "FRole.h"

#include "CPP_Piece.generated.h"

class ACPP_Board;
class UBoxComponent;

UCLASS()
class ALGORITHMS_EXAM_API ACPP_Piece : public AActor
{
	GENERATED_BODY()

	int MaxHealth;

	UPROPERTY()
	ACPP_Board* CurrentBoard;

	UPROPERTY()
	ACPP_Pathfinding* Pathfinding;

	UPROPERTY()
	TArray<UCPP_AlgorithmPath*> LegalPaths;

	
	
public:	
	// Sets default values for this actor's properties
	ACPP_Piece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Effect")
	UNiagaraSystem* NiagaraDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* NiagaraHeal;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	 * Components
	 */

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	USkeletalMeshComponent* MeshComponent;

	/*
	 * Variables
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	F2DVectorInt BoardPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	TArray<F2DVectorInt> MovementOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	FRole PieceRole;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	FColor DefaultTileColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	FColor HighlightedTileColor;

	UPROPERTY()
	int CurrentMovementCost;

	/*
	 * Functions
	 */

	UFUNCTION(BlueprintCallable, Category = "Piece")
	int Damage(int Value);

	UFUNCTION(BlueprintCallable, Category = "Piece")
	bool MoveTo(F2DVectorInt TargetPosition);

	UFUNCTION(BlueprintCallable, Category = "Piece")
	int MoveAlongPath(UCPP_AlgorithmPath* Path);

	UFUNCTION()
	void DestroyPiece();

	UFUNCTION()
	void Onclicked();

	UFUNCTION()
	void GetTile(ACPP_Tile* Tile);


	//Hightlight Functions

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Hightlight")
	void HighlightPiece();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Hightlight")
	void NotHighlightPiece();

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	void VisualizePathfinding(TArray<UCPP_AlgorithmPath*> Paths);

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	void ClearVisualizePathfinding();
};
