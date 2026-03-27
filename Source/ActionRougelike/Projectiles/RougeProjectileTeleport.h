// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RougeProjectile.h"
#include "GameFramework/Actor.h"
#include "RougeProjectileTeleport.generated.h"

UCLASS(Abstract)
class ACTIONROUGELIKE_API ARougeProjectileTeleport : public ARougeProjectile
{
	GENERATED_BODY()

public:
	
	virtual void PostInitializeComponents() override;
	
protected:
	
	FTimerHandle ShootingTimerHandle;
	
	const float DetonateDelay = 0.2f;
	
	FTimerHandle PreTeleportTimerHandle;
	
	const float DelayedTeleportTime = 0.2f;
	
	virtual void BeginPlay() override;
	
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
	void StartDelayedTeleportation();
	
	void DelayedTeleportTimeElapsed();
};
