// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
	
	bool CanStart() const;
	
	bool IsRunning() const
	{
		return bIsRunning;
	}
	
	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StartAction();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StopAction();
	
	float GetCooldownTimeRemaining() const;
	
	UFUNCTION(BlueprintCallable)
	URougeActionSystemComponent* GetOwningComponent() const;
	
	FGameplayTag GetActionName() const
	{
		return ActionName;
	}
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FGameplayTag ActionName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FGameplayTagContainer GrantTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FGameplayTagContainer BlockedTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	TMap<FGameplayTag, float> ConsumeTags;

	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	float CooldownTime = 0.0f;
	
	// GameTime until the Action is available again
	UPROPERTY(Transient)
	float CooldownUntil = 0;
	
	UPROPERTY(Transient)
	bool bIsRunning = false;
};
