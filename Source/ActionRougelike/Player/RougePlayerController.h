// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RougePlayerController.generated.h"

class UInputAction;
class URougeInteractionComponent;
/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API ARougePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<URougeInteractionComponent> InteractionComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Interact;

	void StartInteract();
	
	virtual void SetupInputComponent() override;
	
public:
	
	ARougePlayerController();
};
