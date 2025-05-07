// Fill out your copyright notice in the Description page of Project Settings.

#include "FRole.h"

#include "PaperSprite.h"


FRole::FRole()
{
	RoleTeam = FTeam();
	RoleName = "";
	RoleSprite = nullptr;
}

FRole::FRole(FTeam SetTeam, FString SetName)
{
	RoleTeam = SetTeam;
	RoleName = SetName;
	RoleSprite = nullptr;
}

FRole::FRole(FTeam SetTeam, FString SetName, UTexture2D* SetSprite)
{
	RoleTeam = SetTeam;
	RoleName = SetName;
	RoleSprite = SetSprite;
}

FRole::~FRole()
{
}
