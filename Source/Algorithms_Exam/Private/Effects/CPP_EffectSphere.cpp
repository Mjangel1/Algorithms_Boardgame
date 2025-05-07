// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/CPP_EffectSphere.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"


ACPP_EffectSphere::ACPP_EffectSphere()
{
	EffectType = DAMAGE;
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	TriggerSphere->SetupAttachment(GetRootComponent());
	TriggerSphere->InitSphereRadius(50.0);
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ACPP_EffectSphere::OnBeginOverlap);
	NiagaraComponent = nullptr;
}

void ACPP_EffectSphere::BeginPlay()
{
	Super::BeginPlay();

	if (NiagaraSmoke)
	{
		const FVector Location = TriggerSphere->GetRelativeLocation();
		NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSmoke, Location, FRotator::ZeroRotator);
	}


}




void ACPP_EffectSphere::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool fromSweep, const FHitResult& result)
{

	if (OtherActor->IsA(ACPP_Piece::StaticClass()))
	{
		PieceRef = Cast<ACPP_Piece>(OtherActor);
		PieceRef->Damage(1);
		IsInside = true;
		//DrawDebugBox(GetWorld(), GetActorLocation(), FVector(50, 50, 50), FColor::Black, false, 3.f, 0, 10);
		
	}
	
	else
	{
		
	}
}


void ACPP_EffectSphere::DealDamage(ACPP_Piece* PieceInside)
{
	if (IsInside)
	{
		if (IsValid(PieceRef))
		{
			PieceRef->Damage(1);
			
			
			//DrawDebugBox(GetWorld(), GetActorLocation(), FVector(50, 50, 50), FColor::Black, false, 3.f, 0, 10);
		}
		else
		{
			
		}
	}
}

void ACPP_EffectSphere::UpdateCountEffect()
{
		Count++;
		
		if (Count ==2) //after dealing damage on his turn, player will also deal damage on his next turn
		{
			if (PieceRef)
			{
				DealDamage(PieceRef);
				NiagaraComponent->Deactivate();
				GetWorldTimerManager().SetTimer(DestroySphere, this, &ACPP_EffectSphere::DestroySphereEffect, 1.2f);

				
			}
			else
			{
				NiagaraComponent->Deactivate();
				GetWorldTimerManager().SetTimer(DestroySphere, this, &ACPP_EffectSphere::DestroySphereEffect, 1.2f);

			}
		}
		if (Count > 2) {
			Count = 0;
		}
}

void ACPP_EffectSphere::UpdateCount_Implementation()
{
	UpdateCountEffect();
}

void ACPP_EffectSphere::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(PieceRef)
	{
		PieceRef = nullptr;
	}
}

void ACPP_EffectSphere::DestroySphereEffect()
{
	NiagaraComponent->DestroyComponent();
	Destroy();

}
















