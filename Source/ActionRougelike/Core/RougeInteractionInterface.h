// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RougeInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class URougeInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for objects that can be interacted with.
 * Classes implementing this interface should provide their own implementation for the Interact method.
 */
class ACTIONROUGELIKE_API IRougeInteractionInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void Interact();
};
