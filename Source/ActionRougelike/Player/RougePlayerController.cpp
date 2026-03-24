// Fill out your copyright notice in the Description page of Project Settings.


#include "RougePlayerController.h"

#include "RougeInteractionComponent.h"

ARougePlayerController::ARougePlayerController()
{
	InteractionComponent = CreateDefaultSubobject<URougeInteractionComponent>(TEXT("InteractionComp"));
}
