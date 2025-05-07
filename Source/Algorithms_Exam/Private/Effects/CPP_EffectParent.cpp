// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/CPP_EffectParent.h"

// Sets default values
ACPP_EffectParent::ACPP_EffectParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_EffectParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_EffectParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

