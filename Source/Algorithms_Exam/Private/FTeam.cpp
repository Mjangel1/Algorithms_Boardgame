// Fill out your copyright notice in the Description page of Project Settings.


#include "FTeam.h"

FTeam::FTeam()
{
	TeamName = "";
	TeamColor = FColor::White;
}

FTeam::FTeam(FString SetName, FColor SetColor)
{
	TeamName = SetName;
	TeamColor = SetColor;
}

FTeam::~FTeam()
{
}
