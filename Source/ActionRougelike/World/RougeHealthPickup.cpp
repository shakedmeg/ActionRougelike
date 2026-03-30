// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeHealthPickup.h"

#include "ActionSystem/RougeActionSystemComponent.h"
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
		if (!ActionSystem->IsFullHealth())
		{
			PlayerCharacter->GetActionSystemComponent()->ApplyHealthChange(HealingAmount);
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(), FRotator::ZeroRotator);
			Destroy();
			
			
			Super::OnActorOverlapped(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		}
	}
}
