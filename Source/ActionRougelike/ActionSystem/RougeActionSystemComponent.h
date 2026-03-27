// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RougeActionSystemComponent.generated.h"


struct FRougeAttributeSet
{
		FRougeAttributeSet()
			: Health(100) {}
	
	float Health;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROUGELIKE_API URougeActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	void ApplyHealthChange(float InValueChange);
	
protected:
	
	FRougeAttributeSet Attributes; 

public:
	
	URougeActionSystemComponent();
};
