// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RougeGameTypes.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RougeBTTask_RangedAttack.generated.h"

class ARougeProjectile;
/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API URougeBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
	URougeBTTask_RangedAttack();

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<ARougeProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxBulletSpread = 5.0f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
