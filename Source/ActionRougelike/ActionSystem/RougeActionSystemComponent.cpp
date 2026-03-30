// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeActionSystemComponent.h"


URougeActionSystemComponent::URougeActionSystemComponent()
{
	
}

void URougeActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	float OldHealth = Attributes.Health;
	
	float MaxHealth = Attributes.MaxHealth;
	
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.0f, MaxHealth);
	
	if (!FMath::IsNearlyEqual(OldHealth, Attributes.Health))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	}
	
	
	UE_LOG(LogTemp, Log, TEXT("New Health: %f, Max Health: %f"), Attributes.Health, MaxHealth);
}

bool URougeActionSystemComponent::IsFullHealth()
{
	return Attributes.Health == Attributes.MaxHealth;
}
