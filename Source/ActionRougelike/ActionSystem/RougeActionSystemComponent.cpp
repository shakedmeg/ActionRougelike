// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeActionSystemComponent.h"

#include "RougeAction.h"
#include "RougeAttributeSet.h"
#include "SharedGameplayTags.h"


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

void URougeActionSystemComponent::ApplyAttributeChange(FGameplayTag AttributeTag, float Delta, EAttributeModifyType ModifyType)
{
	FRougeAttribute* FoundAttribute = GetAttribute(AttributeTag);
	check(FoundAttribute);
	
	float OldValue = FoundAttribute->GetValue();
	
	switch (ModifyType)
	{
	case Base:
		FoundAttribute->Base += Delta;
		break;
	case Modifier:
		FoundAttribute->Modifier += Delta;
		break;
	case OverrideBase:
		FoundAttribute->Base = Delta;
		break;
	default:
		check(false);
	}
	
	Attributes->PostAttributeChanged();
	
	if (FOnAttributeChanged* Event = AttributeListeners.Find(AttributeTag))
	{
		Event->Broadcast(AttributeTag, FoundAttribute->GetValue(), OldValue);
	}
	
	UE_LOGFMT(LogTemp, Log, "Attribute: {0}, New: {1}, Old: {2}", AttributeTag.ToString(), FoundAttribute->GetValue(), OldValue);
}

FRougeAttribute* URougeActionSystemComponent::GetAttribute(FGameplayTag InAttributeTag) const
{
	FRougeAttribute* FoundAttribute = *CachedAttributes.Find(InAttributeTag);
	
	return FoundAttribute;
}

FOnAttributeChanged& URougeActionSystemComponent::GetAttributeListener(FGameplayTag InAttributeTag)
{
	return AttributeListeners.FindOrAdd(InAttributeTag);
}
