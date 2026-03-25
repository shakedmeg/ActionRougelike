// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RougePlayerCharacter.generated.h"

class UNiagaraSystem;
class ARougeProjectileMagic;
struct FInputActionInstance;
struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONROUGELIKE_API ARougePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARougePlayerCharacter();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TSubclassOf<ARougeProjectileMagic> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<USoundBase> CastingSound;
	
	UPROPERTY(VisibleAnywhere, Category = "PrimaryAttack")
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UAnimMontage> AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Move;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Look;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Jump;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& InValue);
	
	void Look(const FInputActionInstance& InValue);
	
	void PrimaryAttack();
	
	void AttackTimerElapsed();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
