// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RougeAICharacter.generated.h"

class URougeActionSystemComponent;

UCLASS()
class ACTIONROUGELIKE_API ARougeAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARougeAICharacter();
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<URougeActionSystemComponent> ActionSystemComponent;
};
