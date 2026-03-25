// Fill out your copyright notice in the Description page of Project Settings.


#include "RougePlayerController.h"

#include "EnhancedInputComponent.h"
#include "RougeInteractionComponent.h"

ARougePlayerController::ARougePlayerController()
{
	InteractionComponent = CreateDefaultSubobject<URougeInteractionComponent>(TEXT("InteractionComp"));
}

void ARougePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInput->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ARougePlayerController::StartInteract);
}

void ARougePlayerController::StartInteract()
{
	InteractionComponent->Interact();
}
