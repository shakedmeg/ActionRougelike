// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeCoinPickupSubsystem.h"

void URougeCoinPickupSubsystem::AddCoinPickup(TArray<FVector> NewLocations, TArray<int32> NewAmounts)
{
	CoinLocations.Append(NewLocations);
	CoinAmounts.Append(NewAmounts);
}

void URougeCoinPickupSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UWorld* World = GetWorld();
	
	for (int i = 0; i < CoinLocations.Num(); i++)
	{
		DrawDebugPoint(World, CoinLocations[i], 8.0f, FColor::White);
	}
}
