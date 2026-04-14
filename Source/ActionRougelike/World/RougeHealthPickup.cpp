// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeHealthPickup.h"

#include "SharedGameplayTags.h"
#include "ActionSystem/RougeActionSystemComponent.h"
#include "Core/RougeGameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RougePlayerCharacter.h"

ARougeHealthPickup::ARougeHealthPickup()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARougeHealthPickup::OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARougePlayerCharacter* PlayerCharacter = Cast<ARougePlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		URougeActionSystemComponent* ActionSystem = PlayerCharacter->GetActionSystemComponent();
		if (!URougeGameplayStatics::IsFullHealth(ActionSystem))
		{
			PlayerCharacter->GetActionSystemComponent()->ApplyAttributeChange(SharedGameplayTag::Attribute_Health, HealingAmount, Base);
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(), FRotator::ZeroRotator);
			Destroy();
			
			
			Super::OnActorOverlapped(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		}
	}
}
