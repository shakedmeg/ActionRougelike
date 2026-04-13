// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RougeActionSystemComponent.generated.h"

class URougeAction;

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
	
	void StartAction(FName InActionName);
	void StopAction(FName InActionName);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	void ApplyHealthChange(float InValueChange);

	bool IsFullHealth();
	
	float GetHealth() const;
	
	float GetMaxHealth() const;
	
	virtual void InitializeComponent() override;

	void GrantAction(TSubclassOf<URougeAction> NewActionClass);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FRougeAttributeSet Attributes;
	
	UPROPERTY()
	TArray<TObjectPtr<URougeAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<URougeAction>> DefaultActions;
};
