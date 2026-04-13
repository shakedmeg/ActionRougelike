// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RougeAction.generated.h"

class URougeActionSystemComponent;
/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class ACTIONROUGELIKE_API URougeAction : public UObject
{
	GENERATED_BODY()
	
public:
	
	virtual void StartAction();
	
	URougeActionSystemComponent* GetOwningComponent() const;
	
	FName GetActionName() const
	{
		return ActionName;
	}
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FName ActionName = FName("PrimaryAttack");
	
};
