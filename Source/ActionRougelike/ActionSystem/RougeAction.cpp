// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAction.h"

#include "ActionRougelike.h"
#include "RougeActionSystemComponent.h"
#include "RougeAttributeSet.h"

void URougeAction::StartAction_Implementation()
{
	bIsRunning = true;
	
	float GameTime = GetWorld()->TimeSeconds;
	
	UE_LOGFMT(LogGame, Log, "Started Action {ActionName} - {WorldTime}", ActionName.ToString(), GameTime);
	UE_LOGFMT(LogGame, Log, "Started Action {ActionName} - {WorldTime}", ("ActionName", ActionName.ToString()), ("WorldTime", GameTime));
	
	URougeActionSystemComponent* ActionComponent = GetOwningComponent(); 
	
	ActionComponent->ActiveGameplayTags.AppendTags(GrantTags);
	
	for (auto ConsumeTag : ConsumeTags)
	{
		ActionComponent->ApplyAttributeChange(ConsumeTag.Key, -ConsumeTag.Value, Modifier);
	}
}

void URougeAction::StopAction_Implementation()
{
	bIsRunning = false;
	
	float GameTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogGame, Log, "Stopped Action {ActionName} - {WorldTime}", ActionName.ToString(), GameTime);
	UE_LOGFMT(LogGame, Log, "Stopped Action {ActionName} - {WorldTime}", ("ActionName", ActionName.ToString()), ("WorldTime", GameTime));
	
	CooldownUntil = GetWorld()->TimeSeconds + CooldownTime;
	
	GetOwningComponent()->ActiveGameplayTags.RemoveTags(GrantTags);
}

bool URougeAction::CanStart() const
{
	if (bIsRunning)
	{
		return false;
	}
	
	if (GetCooldownTimeRemaining() >0.0f)
	{
		UE_LOG(LogGame, Log, TEXT("Cooldown remaining: %f"), GetCooldownTimeRemaining());
		return false;
	}
	
	URougeActionSystemComponent* ActionComponent = GetOwningComponent();

	for (auto ConsumeTag : ConsumeTags)
	{
		float BaseAttribute = ActionComponent->GetAttributeValue(ConsumeTag.Key);
		if (BaseAttribute < ConsumeTag.Value)
		{
			return false;
		}
	}
	
	if (ActionComponent->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	
	return true;
}

float URougeAction::GetCooldownTimeRemaining() const
{
	return FMath::Max(0.0f ,CooldownUntil - GetWorld()->TimeSeconds); 
}

URougeActionSystemComponent* URougeAction::GetOwningComponent() const
{
	return Cast<URougeActionSystemComponent>(GetOuter());  
}
