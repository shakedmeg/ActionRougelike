// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RougeAction.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API URougeAction : public UObject
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FName ActionName = FName("PrimaryAttack");

public:
	
	FName GetActionName() const
	{
		return ActionName;
	}
	
	void StartAction();
};
