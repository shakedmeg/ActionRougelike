// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAction.h"
#include "RougeActionSystemComponent.h"

void URougeAction::StartAction_Implementation()
{
	bIsRunning = true;
	
	float GameTime = GetWorld()->TimeSeconds;
	
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", ActionName.ToString(), GameTime);
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", ("ActionName", ActionName.ToString()), ("WorldTime", GameTime));
	
	CooldownUntil = GetWorld()->TimeSeconds + CooldownTime;
}

void URougeAction::StopAction_Implementation()
{
	bIsRunning = false;
	
	float GameTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Stopped Action {ActionName} - {WorldTime}", ActionName.ToString(), GameTime);
	UE_LOGFMT(LogTemp, Log, "Stopped Action {ActionName} - {WorldTime}", ("ActionName", ActionName.ToString()), ("WorldTime", GameTime));
}

bool URougeAction::CanStart() const
{
	if (bIsRunning)
	{
		return false;
	}
	
	if (GetCooldownTimeRemaining() >0.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("Cooldown remaining: %f"), GetCooldownTimeRemaining());
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
