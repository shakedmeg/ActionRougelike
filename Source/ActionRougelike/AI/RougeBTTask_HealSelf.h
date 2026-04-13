// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RougeBTTask_HealSelf.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API URougeBTTask_HealSelf : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float HealingAmount = 50.0f;
	
public:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
