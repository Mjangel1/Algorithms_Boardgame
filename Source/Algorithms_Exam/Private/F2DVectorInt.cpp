// Fill out your copyright notice in the Description page of Project Settings.


#include "F2DVectorInt.h"

F2DVectorInt::F2DVectorInt()
{
	X = 0;
	Y = 0;
}

F2DVectorInt::F2DVectorInt(const int SetX, const int SetY)
{
	X = SetX;
	Y = SetY;
}

F2DVectorInt::~F2DVectorInt()
{

}

/// <summary>
/// Returns whether this F2DVectorInt is between the values of Min and Max.
/// </summary>
/// <param name="Min"> Smallest F2DVectorInt value </param>
/// <param name="Max"> Largest F2DVectorInt value</param>
/// <returns> Is this F2DVectorInt between Min and Max </returns>
bool F2DVectorInt::WithinRange(const F2DVectorInt& Min, const F2DVectorInt& Max) const
{
	return (X >= Min.X && X <= Max.X && Y >= Min.Y && Y <= Max.Y);
}

/// <summary>
/// Returns whether this F2DVectorInt is between the values of (0,0) and Max.
/// </summary>
/// <param name="Max"> Largest F2DVectorInt value</param>
/// <returns> Is this F2DVectorInt between (0,0) and Max </returns>
bool F2DVectorInt::WithinRange(const F2DVectorInt& Max) const
{
	return (X >= 0 && X <= Max.X && Y >= 0 && Y <= Max.Y);
}

F2DVectorInt F2DVectorInt::operator+(const F2DVectorInt& Other) const
{
	return F2DVectorInt(X + Other.X, Y + Other.Y);
}

F2DVectorInt F2DVectorInt::operator-(const F2DVectorInt& Other) const
{
	return F2DVectorInt(X - Other.X, Y - Other.Y);
}

bool F2DVectorInt::operator==(const F2DVectorInt& Other) const
{
	return (X == Other.X && Y == Other.Y);
}
