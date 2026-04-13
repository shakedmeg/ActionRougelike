// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAction.h"

void URougeAction::StartAction()
{
	float GameTime = 0.0f;
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", ActionName, GameTime);
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", ("ActionName", ActionName), ("WorldTime", GameTime));
}
