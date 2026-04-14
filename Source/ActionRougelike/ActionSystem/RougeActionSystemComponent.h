// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "RougeActionSystemComponent.generated.h"

struct FGameplayTag;
class URougeAction;
class URougeAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROUGELIKE_API URougeActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	URougeActionSystemComponent();
	
	void StartAction(FGameplayTag InActionName);
	void StopAction(FGameplayTag InActionName);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	void ApplyHealthChange(float InValueChange);

	bool IsFullHealth();
	
	float GetHealth() const;
	
	float GetMaxHealth() const;
	
	virtual void InitializeComponent() override;

	void GrantAction(TSubclassOf<URougeAction> NewActionClass);
	
	FGameplayTagContainer ActiveGameplayTags; 

protected:
	
	UPROPERTY()
	TObjectPtr<URougeAttributeSet> Attributes;
	
	UPROPERTY(EditAnywhere, Category = Attributes, NoClear)
	TSubclassOf<URougeAttributeSet> AttributeSetClass;
	
	UPROPERTY()
	TArray<TObjectPtr<URougeAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<URougeAction>> DefaultActions;
};
