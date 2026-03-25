// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeInteractionComponent.h"

#include "Core/RougeInteractionInterface.h"
#include "Engine/OverlapResult.h"

URougeInteractionComponent::URougeInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URougeInteractionComponent::Interact()
{
	IRougeInteractionInterface* InteractInterface = Cast<IRougeInteractionInterface>(SelectedActor);
	if (InteractInterface)
	{
		InteractInterface->Interact();
	}
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
	
	AActor* BestActor = nullptr;
	float HighestDotResult = -1.0f;
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();
		
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		if (DotResult > HighestDotResult)
		{
			BestActor = Overlap.GetActor();
			HighestDotResult = DotResult;
		}
		
		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.f), FColor::Red);
		FString DebugString = FString::Printf(TEXT("Dot: %f"), DotResult);
		DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0.0f, true);
	}
	
	SelectedActor = BestActor;
	
	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.f), FColor::Green);
	}
	
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32.0f, FColor::White);
}

