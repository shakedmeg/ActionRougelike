// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RougeAction.h"
#include "RougeAction_ProjectileAttack.generated.h"

class URougeActionSystemComponent;
class ARougeProjectile;
class UNiagaraSystem;
class USoundBase;
class UAnimMontage;

/**
 * 
 */
UCLASS(Abstract)
class ACTIONROUGELIKE_API URougeAction_ProjectileAttack : public URougeAction
{
	GENERATED_BODY()
	
	URougeAction_ProjectileAttack();
	
	void AttackTimerElapsed();
	
public:
	
	virtual void StartAction() override;
	

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileAttack")
	TSubclassOf<ARougeProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileAttack")
	TObjectPtr<USoundBase> CastingSound;
	
	UPROPERTY(VisibleAnywhere, Category = "ProjectileAttack")
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileAttack")
	TObjectPtr<UAnimMontage> AttackMontage;
};
