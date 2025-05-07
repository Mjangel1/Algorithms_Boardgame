// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/CPP_EffectLocation.h"

ACPP_EffectLocation::ACPP_EffectLocation()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EffectType = LOCATION;
}