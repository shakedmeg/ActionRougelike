// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeGameplayStatics.h"

#include "SharedGameplayTags.h"
#include "ActionSystem/RougeActionSystemComponent.h"
#include "ActionSystem/RougeAttributeSet.h"

bool URougeGameplayStatics::IsFullHealth(URougeActionSystemComponent* ActionComp)
{
	FRougeAttribute* Health = ActionComp->GetAttribute(SharedGameplayTag::Attribute_Health);
	FRougeAttribute* MaxHealth = ActionComp->GetAttribute(SharedGameplayTag::Attribute_MaxHealth);
	
	return FMath::IsNearlyEqual(Health->GetValue(), MaxHealth->GetValue());
}
