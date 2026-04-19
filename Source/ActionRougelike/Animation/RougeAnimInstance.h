// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RougeAnimInstance.generated.h"

class URougeActionSystemComponent;
/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API URougeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	
	UPROPERTY(Transient, BlueprintReadOnly, Category = StatusEffects)
	bool bIsSprinting;
	
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<URougeActionSystemComponent> ActionComp;
};
