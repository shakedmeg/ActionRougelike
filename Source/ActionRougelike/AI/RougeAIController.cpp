// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


ARougeAIController::ARougeAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARougeAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(BehaviorTree);
	
	FName TargetActor = FName("TargetActor");
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	check(PlayerPawn);
	
	GetBlackboardComponent()->SetValueAsObject(TargetActor, PlayerPawn);
}

