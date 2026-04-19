// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAICharacter.h"

#include "SharedGameplayTags.h"
#include "ActionSystem/RougeActionSystemComponent.h"
#include "ActionSystem/RougeAttributeSet.h"


ARougeAICharacter::ARougeAICharacter()
{
	ActionSystemComponent = CreateDefaultSubobject<URougeActionSystemComponent>(TEXT("ActionSystemComp"));
	ActionSystemComponent->SetDefaultAttributeSet(URougeMonsterAttributeSet::StaticClass());
}

float ARougeAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	ActionSystemComponent->ApplyAttributeChange(SharedGameplayTag::Attribute_Health, -ActualDamage, Base);
	
	GetMesh()->SetOverlayMaterialMaxDrawDistance(0);
	
	// GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	GetMesh()->SetCustomPrimitiveDataFloat(0, GetWorld()->TimeSeconds);
	
	GetWorldTimerManager().SetTimer(OverlayTimerHandle, [this]()
	{
		GetMesh()->SetOverlayMaterialMaxDrawDistance(1);
	}, 1.0f, false);
	
	return ActualDamage;
}
