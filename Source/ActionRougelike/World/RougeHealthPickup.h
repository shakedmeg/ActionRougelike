// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RougePickupActor.h"
#include "RougeHealthPickup.generated.h"

class ARougePlayerCharacter;

UCLASS()
class ACTIONROUGELIKE_API ARougeHealthPickup : public ARougePickupActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARougeHealthPickup();
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float HealingAmount = 50.0f;
	
	virtual void OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
