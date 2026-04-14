// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeActionSystemComponent.h"

#include "RougeAction.h"
#include "RougeAttributeSet.h"


URougeActionSystemComponent::URougeActionSystemComponent()
{
	bWantsInitializeComponent = true;
	
	AttributeSetClass = URougeAttributeSet::StaticClass();
}

void URougeActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	Attributes = NewObject<URougeAttributeSet>(this, AttributeSetClass);
	
	for (TFieldIterator<FStructProperty> PropIt(Attributes->GetClass()); PropIt; ++PropIt)
	{
		FRougeAttribute* FoundAttribute = PropIt->ContainerPtrToValuePtr<FRougeAttribute>(Attributes);
		
		PropIt->GetName();
		
		FName AttributeTagName = FName("Attribute." + PropIt->GetName());
		FGameplayTag AttributeTag = FGameplayTag::RequestGameplayTag(AttributeTagName);
		CachedAttributes.Add(AttributeTag, FoundAttribute);
	}
	

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

void URougeActionSystemComponent::StartAction(FGameplayTag InActionName)
{
	for (URougeAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			if (Action->CanStart())
			{
				Action->StartAction();
			}
			return;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("No Action found with name %s"), *InActionName.ToString());
}

void URougeActionSystemComponent::StopAction(FGameplayTag InActionName)
{
	for (URougeAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StopAction();
			return;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("No Action found with name %s"), *InActionName.ToString());
}

void URougeActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	// float OldHealth = Attributes.Health;
	//
	// float MaxHealth = Attributes.MaxHealth;
	//
	// Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.0f, MaxHealth);
	//
	// if (!FMath::IsNearlyEqual(OldHealth, Attributes.Health))
	// {
	// 	OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	// }
	//
	//
	// UE_LOG(LogTemp, Log, TEXT("New Health: %f, Max Health: %f"), Attributes.Health, MaxHealth);
}

bool URougeActionSystemComponent::IsFullHealth()
{
	// return Attributes.Health == Attributes.MaxHealth;
	return true;
}

FRougeAttribute* URougeActionSystemComponent::GetAttribute(FGameplayTag InAttributeTag) const
{
	FRougeAttribute* FoundAttribute = *CachedAttributes.Find(InAttributeTag);
	
	return FoundAttribute;
}
