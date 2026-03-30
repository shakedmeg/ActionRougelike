// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RougeActionSystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FRougeAttributeSet
{
	GENERATED_BODY()
	
	FRougeAttributeSet() :
	Health(100),
	MaxHealth(100) {}

	UPROPERTY(BlueprintReadOnly)
	float Health;
	
	UPROPERTY(BlueprintReadOnly)
	float MaxHealth;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROUGELIKE_API URougeActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	URougeActionSystemComponent();
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	void ApplyHealthChange(float InValueChange);

	bool IsFullHealth();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FRougeAttributeSet Attributes;
};
