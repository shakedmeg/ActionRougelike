// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeBTTask_HealSelf.h"

#include "AIController.h"
#include "SharedGameplayTags.h"
#include "ActionSystem/RougeActionSystemComponent.h"


class URougeActionSystemComponent;

EBTNodeResult::Type URougeBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	check(Pawn);
	
	
	URougeActionSystemComponent* ActionComp = Pawn->GetComponentByClass<URougeActionSystemComponent>();
	
	if (ensure(ActionComp))
	{
		ActionComp->ApplyAttributeChange(SharedGameplayTag::Attribute_Health, HealingAmount, Base);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
