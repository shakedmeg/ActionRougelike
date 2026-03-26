// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RougeExplosiveBarrel.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class URadialForceComponent;

UCLASS()
class ACTIONROUGELIKE_API ARougeExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARougeExplosiveBarrel();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "ExplosiveBarrel")
	float ExplosionDelay = 3.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> BurningEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> LoopedBurningSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	bool bDidExplode;
	
	FTimerHandle ExplosionTimerHandle;
	
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveBurningEffectComp;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> ActiveBurningSoundComp;
	
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintCallable)
	void Explode();
};
