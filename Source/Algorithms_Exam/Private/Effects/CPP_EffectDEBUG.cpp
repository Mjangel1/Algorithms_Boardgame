// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/CPP_EffectDEBUG.h"

ACPP_EffectDEBUG::ACPP_EffectDEBUG()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EffectType = UNDEFINED;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetBoundsScale(10);

	SecondsUntilDestroy = 5.f;
}

// Called when the game starts or when spawned
void ACPP_EffectDEBUG::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ACPP_EffectDEBUG::DestroyAfterTime, SecondsUntilDestroy);
}

void ACPP_EffectDEBUG::DestroyAfterTime()
{
	Destroy();
}
