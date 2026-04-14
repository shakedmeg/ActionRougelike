// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAttributeSet.h"

URougeHealthAttributeSet::URougeHealthAttributeSet()
{
	Health = FRougeAttribute(100);
	MaxHealth = FRougeAttribute(Health.GetValue());
}
