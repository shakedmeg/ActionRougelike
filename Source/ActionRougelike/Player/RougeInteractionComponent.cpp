// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeInteractionComponent.h"

URougeInteractionComponent::URougeInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URougeInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	
	FVector Center = PC->GetPawn()->GetActorLocation();
	
	DrawDebugBox(GetWorld(), Center, FVector(20.f), FColor::Red);
}

