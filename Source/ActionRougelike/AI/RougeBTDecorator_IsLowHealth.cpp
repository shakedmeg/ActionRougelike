// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeBTDecorator_IsLowHealth.h"

#include "AIController.h"
#include "ActionSystem/RougeActionSystemComponent.h"

bool URougeBTDecorator_IsLowHealth::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	// BT should have been stopped already with no pawn
	check(Pawn);
	
	URougeActionSystemComponent* ActionComp = Pawn->GetComponentByClass<URougeActionSystemComponent>();
	
	if (ensure(ActionComp))
	{
		return (ActionComp->GetHealth() / ActionComp->GetMaxHealth()) < LowHealthThreshold;
	}
	
	return false;
}
