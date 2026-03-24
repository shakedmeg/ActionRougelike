// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RougePlayerController.generated.h"

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
	
public:
	
	ARougePlayerController();
};
