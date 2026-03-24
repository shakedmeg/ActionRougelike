// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RougeProjectileMagic.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraComponent;
class UAudioComponent;

UCLASS(Abstract)
class ACTIONROUGELIKE_API ARougeProjectileMagic : public AActor
{
	GENERATED_BODY()

public:
	
	virtual void PostInitializeComponents() override;
	
	ARougeProjectileMagic();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DmgTypeClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UAudioComponent> LoopedAudioComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
