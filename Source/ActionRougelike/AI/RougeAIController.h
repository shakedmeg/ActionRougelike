// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "RougeAIController.generated.h"

class UBehaviorTree;

UCLASS()
class ACTIONROUGELIKE_API ARougeAIController : public AAIController
{
	GENERATED_BODY()

public:
	ARougeAIController();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	virtual void BeginPlay() override;
};
