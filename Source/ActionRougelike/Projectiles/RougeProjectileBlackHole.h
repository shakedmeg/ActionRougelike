// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RougeProjectile.h"
#include "GameFramework/Actor.h"
#include "RougeProjectileBlackHole.generated.h"

class URadialForceComponent;

UCLASS(Abstract)
class ACTIONROUGELIKE_API ARougeProjectileBlackHole : public ARougeProjectile
{
	GENERATED_BODY()
	
public:
	
	virtual void PostInitializeComponents() override;

	ARougeProjectileBlackHole();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	UFUNCTION()
	void OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
