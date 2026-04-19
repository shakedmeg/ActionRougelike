// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAnimInstance.h"

#include "SharedGameplayTags.h"
#include "ActionSystem/RougeActionSystemComponent.h"

void URougeAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	ActionComp = GetOwningActor()->FindComponentByClass<URougeActionSystemComponent>();
}

void URougeAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (ActionComp)
	{
		bIsSprinting = ActionComp->ActiveGameplayTags.HasTag(SharedGameplayTag::StatusEffect_Sprinting);
	}
}
