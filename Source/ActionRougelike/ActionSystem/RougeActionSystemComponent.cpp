// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeActionSystemComponent.h"
#include "RougeAction.h"
#include "RougeAttributeSet.h"


URougeActionSystemComponent::URougeActionSystemComponent()
{
	bWantsInitializeComponent = true;
}

void URougeActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	// Fallback for Blueprint and CPP having not yet defined a default
	if (Attributes == nullptr)
	{
		Attributes = NewObject<URougeAttributeSet>(this, URougeAttributeSet::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("No default AttributeSet. Set using SetDefaultAttributeSet() "
								"during Actor Construction or assign in Blueprint ActionComponent for %s"), *GetNameSafe(GetOwner()));
	}
	
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

void URougeActionSystemComponent::SetDefaultAttributeSet(TSubclassOf<URougeAttributeSet> AttributeSetClass)
{
	check(!HasBeenInitialized());
	
	// Only available during constructors of UObjects
	FObjectInitializer& ObjectInitializer = FObjectInitializer::Get();
	Attributes = Cast<URougeAttributeSet>(ObjectInitializer.CreateDefaultSubobject(this, TEXT("Attributes"), AttributeSetClass,  AttributeSetClass));
}

void URougeActionSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	Attributes->InitializeAttributes();
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
	
	// Native C++ listeners 
	if (FOnAttributeChanged* Event = AttributeListeners.Find(AttributeTag))
	{
		Event->Broadcast(AttributeTag, FoundAttribute->GetValue(), OldValue);
	}
	
	// Blueprint listeners
	if (TArray<FOnAttributeDynamicChanged>* Events = AttributeDynamicListeners.Find(AttributeTag))
	{
		for (int i = Events->Num() - 1; i >= 0; --i)
		{
			FOnAttributeDynamicChanged& Event = (*Events)[i];
			bool bIsBound = Event.ExecuteIfBound(AttributeTag, FoundAttribute->GetValue(), OldValue);
			if (!bIsBound)
			{
				Events->RemoveAt(i);
				UE_LOG(LogTemp, Log, TEXT("Cleaned up expired attribute delegate for %s"), *GetNameSafe(GetOwner()));
			}
		}
	}
	
	UE_LOGFMT(LogTemp, Log, "Attribute: {0}, New: {1}, Old: {2}", AttributeTag.ToString(), FoundAttribute->GetValue(), OldValue);
}

FRougeAttribute* URougeActionSystemComponent::GetAttribute(FGameplayTag InAttributeTag) const
{
	FRougeAttribute* FoundAttribute = *CachedAttributes.Find(InAttributeTag);
	
	return FoundAttribute;
}

float URougeActionSystemComponent::GetAttributeValue(FGameplayTag InAttributeTag) const
{
	FRougeAttribute* FoundAttribute = GetAttribute(InAttributeTag);
	return FoundAttribute->GetValue();
}

FOnAttributeChanged& URougeActionSystemComponent::GetAttributeListener(FGameplayTag InAttributeTag)
{
	return AttributeListeners.FindOrAdd(InAttributeTag);
}

void URougeActionSystemComponent::AddDynamicAttributeListener(FOnAttributeDynamicChanged Event,
	FGameplayTag AttributeTag)
{
	TArray<FOnAttributeDynamicChanged>& Events = AttributeDynamicListeners.FindOrAdd(AttributeTag);
	Events.Add(Event);
}

void URougeActionSystemComponent::RemoveDynamicAttributeListener(FOnAttributeDynamicChanged Event)
{
	for (TPair<FGameplayTag, TArray<FOnAttributeDynamicChanged>>& Listener : AttributeDynamicListeners)
	{
		if (Listener.Value.RemoveSingle(Event) > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("successfully removed blueprint binding"));
			break;
		}
	}
}
