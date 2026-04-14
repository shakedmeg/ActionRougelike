// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAttributeSet.h"

URougeHealthAttributeSet::URougeHealthAttributeSet()
{
	Health = FRougeAttribute(100);
	MaxHealth = FRougeAttribute(Health.GetValue());
}

void URougeHealthAttributeSet::PostAttributeChanged()
{
	Health.Base = FMath::Clamp(Health.Base, 0.0f, MaxHealth.GetValue());
}
