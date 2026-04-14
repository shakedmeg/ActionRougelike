// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAttributeSet.h"

#include "RougeActionSystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


URougePawnAttributeSet::URougePawnAttributeSet()
{
	MoveSpeed = FRougeAttribute(550.0f);
}

URougeMonsterAttributeSet::URougeMonsterAttributeSet()
{
	MoveSpeed = FRougeAttribute(450.0f);
}

URougeHealthAttributeSet::URougeHealthAttributeSet()
{
	Health = FRougeAttribute(100);
	MaxHealth = FRougeAttribute(Health.GetValue());
}

void URougeHealthAttributeSet::PostAttributeChanged()
{
	Health.Base = FMath::Clamp(Health.Base, 0.0f, MaxHealth.GetValue());
}

void URougePawnAttributeSet::InitializeAttributes()
{
	Super::InitializeAttributes();
	
	ApplyMoveSpeed();
}

void URougePawnAttributeSet::PostAttributeChanged()
{
	Super::PostAttributeChanged();
	ApplyMoveSpeed();
}

void URougePawnAttributeSet::ApplyMoveSpeed()
{
	ACharacter* OwningCharacter = Cast<ACharacter>(GetOwningComponent()->GetOwner());
	OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = MoveSpeed.GetValue();	
}

URougeActionSystemComponent* URougeAttributeSet::GetOwningComponent() const
{
	return Cast<URougeActionSystemComponent>(GetOuter()); 
}
