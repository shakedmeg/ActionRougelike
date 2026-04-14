// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RougeAttributeSet.generated.h"

USTRUCT()
struct FRougeAttribute
{
	GENERATED_BODY()
	
	FRougeAttribute() {}
	
	FRougeAttribute(float InBase) 
		: Base(InBase) {}
	
	UPROPERTY(EditAnywhere)
	float Base = 0.0f;
	
	UPROPERTY(Transient)
	float Modifier = 0.0f;
	
	float GetValue()
	{
		return Base + Modifier;
	}
};


/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API URougeAttributeSet : public UObject
{
	GENERATED_BODY()
	
public:
	
	virtual void PostAttributeChanged() {};
};


UCLASS()
class URougeHealthAttributeSet : public URougeAttributeSet
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category = Attributes)
	FRougeAttribute Health;
	
	UPROPERTY(EditAnywhere, Category = Attributes)
	FRougeAttribute MaxHealth;
	
	virtual void PostAttributeChanged() override;
	
	URougeHealthAttributeSet();
	
};
