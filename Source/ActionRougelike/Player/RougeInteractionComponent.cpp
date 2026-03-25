// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeInteractionComponent.h"

#include "Engine/OverlapResult.h"

URougeInteractionComponent::URougeInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URougeInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	
	FVector Center = PC->GetPawn()->GetActorLocation();
	
	// DrawDebugBox(GetWorld(), Center, FVector(20.f), FColor::Red);
	
	ECollisionChannel CollisionChannel = ECC_Visibility;
	
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	TArray<FOverlapResult> Overlaps;
	
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32.0f, FColor::White);
	
	
	AActor* BestActor = nullptr;
	float HighestDotResult = -1.0f;
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.f), FColor::Red);
		
		FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();
		
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		
		FString DebugString = FString::Printf(TEXT("Dot: %f"), DotResult);
		
		DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0.0f, true);
		
		if (DotResult > HighestDotResult)
		{
			BestActor = Overlap.GetActor();
			HighestDotResult = DotResult;
		}
	}
	
	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.f), FColor::Green);
	}
}

