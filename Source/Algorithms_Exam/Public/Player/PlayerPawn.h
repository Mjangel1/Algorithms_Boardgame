// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Piece.h"
#include "GameFramework/DefaultPawn.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "PlayerPawn.generated.h"

/**
 * 
 */


enum my_enum
{
	Default,
	Clicked,
	MoveOrAttack


};



UCLASS()
class ALGORITHMS_EXAM_API APlayerPawn : public ADefaultPawn
{
	GENERATED_BODY()

	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Camera")
	float Sensativity;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	//Enum
	my_enum EDefault = Default;

	UPROPERTY()
	bool bRightMouseButton = false;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* Camera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	class UInputMappingContext* Imc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	class UInputAction* Wasd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	class UInputAction* ClickLeftAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	class UInputAction* ClickRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Player Component")
	class UPlayerComponent* PlayerComponent;



	UPROPERTY(BlueprintReadOnly, category = "Piece")
	ACPP_Piece* SavedPiece = nullptr;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FTeam PlayerTeam;

	UFUNCTION()
	void PlayerMovement(const FInputActionValue& Value);

	UFUNCTION()
	void CameraLook(const FInputActionValue& Value);

	UFUNCTION()
	void OnClick();

	UFUNCTION()
	bool CheckActor(AActor* Actor);

	UFUNCTION()
	void RightMouseButtonIsclicked();

	UFUNCTION()
	void RightMouseButtonNotclicked();

	UFUNCTION()
	void SavePreviousPiece(ACPP_Piece* ClickedPiece);


	UFUNCTION()
	void Deselect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowCards();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideCards();

	UFUNCTION(BlueprintCallable)
	void CardWasUsed();

};
