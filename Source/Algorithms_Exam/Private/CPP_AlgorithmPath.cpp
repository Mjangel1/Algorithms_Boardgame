// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AlgorithmPath.h"

UCPP_AlgorithmPath::UCPP_AlgorithmPath()
{
	Position = F2DVectorInt(-1, -1);
	PathCost = -1;
	Parent = nullptr;
}

UCPP_AlgorithmPath::UCPP_AlgorithmPath(F2DVectorInt SetPosition)
{
	Position = SetPosition;
	PathCost = -1;
	Parent = nullptr;
}

UCPP_AlgorithmPath::UCPP_AlgorithmPath(F2DVectorInt SetPosition, int SetPathCost, UCPP_AlgorithmPath* SetParent)
{
	Position = SetPosition;
	PathCost = SetPathCost;
	Parent = SetParent;
}