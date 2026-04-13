// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeActionSystemComponent.h"

#include "RougeAction.h"


URougeActionSystemComponent::URougeActionSystemComponent()
{
	bWantsInitializeComponent = true;
}

void URougeActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	for (TSubclassOf<URougeAction> ActionClass : DefaultActions)
	{
		if (ensure(ActionClass))
		{
			GrantAction(ActionClass);
		}
	}
}

void URougeActionSystemComponent::GrantAction(TSubclassOf<URougeAction> NewActionClass)
{
	URougeAction* NewAction = NewObject<URougeAction>(this, NewActionClass);
	Actions.Add(NewAction);
}

void URougeActionSystemComponent::StartAction(FName InActionName)
{
	for (URougeAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StartAction();
			return;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("No Action found with name %s"), *InActionName.ToString());
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

float URougeActionSystemComponent::GetHealth() const
{
	return Attributes.Health;
}

float URougeActionSystemComponent::GetMaxHealth() const
{
	return Attributes.MaxHealth;
}