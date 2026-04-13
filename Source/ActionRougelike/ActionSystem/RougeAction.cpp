// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAction.h"
#include "RougeActionSystemComponent.h"

void URougeAction::StartAction_Implementation()
{
	float GameTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", ActionName, GameTime);
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", ("ActionName", ActionName), ("WorldTime", GameTime));
}

void URougeAction::StopAction_Implementation()
{
	float GameTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Stopped Action {ActionName} - {WorldTime}", ActionName, GameTime);
	UE_LOGFMT(LogTemp, Log, "Stopped Action {ActionName} - {WorldTime}", ("ActionName", ActionName), ("WorldTime", GameTime));
}

URougeActionSystemComponent* URougeAction::GetOwningComponent() const
{
	return Cast<URougeActionSystemComponent>(GetOuter());  
}
