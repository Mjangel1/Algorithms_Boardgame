// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CountingSort.h"
TArray<ACPP_Card*> UCPP_CountingSort::Sort(TArray<ACPP_Card*> CardsForSorting)
{
	int32 n = CardsForSorting.Num();

	if (n > 0 && n < 9) {     //if the character piece dies, the max amount of cards wont be 8 anymore
		int32 EvenNumber = n % 2; //we only allow sorting when the hand is full (2 cards of each type), so amount must be even number
		if (EvenNumber == 0) {
			const int32 max = 4; //we know that we only have 4 classes of cards, so the max number is always 4

			int32 count[max + 1] = { 0 }; // initializing count array with starting values 0 will be used for storing how often numbers repeat

			// we know that each card will always repeat twice
			for (int32 i = 0; i < n; i++) {
				count[CardsForSorting[i]->CardRole.ClassIndex] = 2;
				//count[CardsForSorting[i]]++; //if frequency is different than 2 each
			}


			// prefix sum except for the first element and update the count array 
			for (int32 i = 1; i <= max; i++) {
				count[i] = count[i] + count[i - 1];
			}

			
			TArray<ACPP_Card*> Sorted;
			Sorted.SetNum(n);
			for (int32 i = n - 1; i >= 0; i--) {
				Sorted[--count[CardsForSorting[i]->CardRole.ClassIndex]] = CardsForSorting[i];
			}

			// copying the content of sorted array to the original cards array
			for (int32 i = 0; i < n; i++) {
				CardsForSorting[i] = Sorted[i];

			}
			/*GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("sorted")));*/
		}
		else {
			/*GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("error")));*/
		}

	}
	else {
		/*GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("error")));*/
	}

	return CardsForSorting;
}

