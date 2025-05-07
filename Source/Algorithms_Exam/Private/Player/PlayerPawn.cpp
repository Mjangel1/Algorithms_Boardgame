// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "CPP_Piece.h"
#include "CPP_Tile.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerComponent.h"

APlayerPawn::APlayerPawn()
{

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	// this allow the camera to rotate
	Camera->bUsePawnControlRotation = true;

	PlayerComponent = CreateDefaultSubobject<UPlayerComponent>(TEXT("Player Component"));

	Sensativity = 0;

}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(Imc, 0);
		}
	}
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(Wasd, ETriggerEvent::Triggered, this, &APlayerPawn::PlayerMovement);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerPawn::CameraLook);
	EnhancedInputComponent->BindAction(ClickLeftAction, ETriggerEvent::Triggered, this, &APlayerPawn::OnClick);

	EnhancedInputComponent->BindAction(ClickRightAction, ETriggerEvent::Ongoing, this, &APlayerPawn::RightMouseButtonIsclicked);
	EnhancedInputComponent->BindAction(ClickRightAction, ETriggerEvent::Completed, this, &APlayerPawn::RightMouseButtonNotclicked);
}

void APlayerPawn::PlayerMovement(const FInputActionValue& Value)
{

	const FVector2D MoveInput = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator YawPlayerRotation = FRotator(0, GetControlRotation().Yaw, 0);

		FRotator UpDirection = FRotator(GetControlRotation().Pitch,0,0);
		const FVector ForwardBackwards = Camera->GetForwardVector();

		const FVector RightDirection = FRotationMatrix(YawPlayerRotation).GetUnitAxis(EAxis::Y);

		
		AddMovementInput(ForwardBackwards, MoveInput.Y);
		AddMovementInput(RightDirection, MoveInput.X);
	}

}

void APlayerPawn::CameraLook(const FInputActionValue& Value)
{

	const FVector2D LookInput = Value.Get<FVector2D>();

	if (Controller != nullptr && bRightMouseButton)
	{
		AddControllerYawInput(LookInput.X *Sensativity);

		AddControllerPitchInput(LookInput.Y* Sensativity);

	}

}

void APlayerPawn::OnClick()
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(this);

	if (UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult))
	{

		if (EDefault == Clicked)
		{

			if (SavedPiece != nullptr)
			{
				ACPP_Tile* TileClicked = Cast<ACPP_Tile>(HitResult.GetActor());
				if (IsValid(TileClicked))
				{

					SavedPiece->GetTile(TileClicked);
					Deselect();

				}


			}

			if (HitResult.GetActor() == SavedPiece)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Going to buy milk"));
				Deselect();

			}
			if (EDefault == Default)
			{
				return;

			}


		}

		if (EDefault == Default)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("new"));
			if (IsValid(HitResult.GetActor()))
			{

				// check if the player clicked on a piece.
				if (CheckActor(HitResult.GetActor()))
				{
					ACPP_Piece* Piece = Cast<ACPP_Piece>(HitResult.GetActor());
					// access the piece that the player clicked
					Piece->Onclicked();
					SavePreviousPiece(Piece);
					ShowCards();
					EDefault = Clicked;
					//PlayerComponent->ActionCost(1);
					//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%s"), *Piece->GetOwner()->GetName()));
				}
			}

		}
		
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%s"), *HitResult.GetActor()->GetOwner()->GetName()));

	}

}

bool APlayerPawn::CheckActor(AActor* Actor)
{
	
	if (Actor !=nullptr)
	{
		ACPP_Piece* Piece = Cast<ACPP_Piece>(Actor);
		
		if (Piece != nullptr)
		{
			
			if (PlayerComponent->PieceBelongToPlayer(Piece))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Its true"));

				return true;
				

			}
			else
			{
				/*if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Not my piece"));
				}*/
				
			}
			

		}
		else
		{
			/*if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, Actor->GetName());
			}
			*/
		}
	}

	return false;
}

void APlayerPawn::RightMouseButtonIsclicked()
{

	bRightMouseButton = true;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("ay"));

}

void APlayerPawn::RightMouseButtonNotclicked()
{

	bRightMouseButton = false;
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Noo"));
	}*/
	
}

void APlayerPawn::SavePreviousPiece(ACPP_Piece* ClickedPiece)
{
	if (!ClickedPiece) return;

	SavedPiece = ClickedPiece;
	SavedPiece->HighlightPiece();
	if (SavedPiece == nullptr)
	{
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("you aint' getting this"));
		}
		*/
	}
	else
	{
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("give it to me"));
		}
		*/
	}
	

}


void APlayerPawn::Deselect()
{
	EDefault = Default;

	if (!SavedPiece)
	{
		return;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Deselected"));
	HideCards();
	SavedPiece->NotHighlightPiece();
	SavedPiece->ClearVisualizePathfinding();

	SavedPiece = nullptr;
	
}

void APlayerPawn::CardWasUsed()
{

	Deselect();
}

void APlayerPawn::HideCards_Implementation()
{
}

void APlayerPawn::ShowCards_Implementation()
{
}




