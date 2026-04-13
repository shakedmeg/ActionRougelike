// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAICharacter.h"

#include "ActionSystem/RougeActionSystemComponent.h"


ARougeAICharacter::ARougeAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ActionSystemComponent = CreateDefaultSubobject<URougeActionSystemComponent>(TEXT("ActionSystemComp"));
}

float ARougeAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	ActionSystemComponent->ApplyHealthChange(-ActualDamage);
	
	return ActualDamage;
}
