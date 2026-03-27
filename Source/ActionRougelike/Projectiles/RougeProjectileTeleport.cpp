// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeProjectileTeleport.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


void ARougeProjectileTeleport::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ProjectileMovementComponent->InitialSpeed = 6000.f; 
}

void ARougeProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ShootingTimerHandle, this, &ARougeProjectileTeleport::StartDelayedTeleportation, DetonateDelay);
}

void ARougeProjectileTeleport::StartDelayedTeleportation()
{
	ProjectileMovementComponent->StopMovementImmediately();
	LoopedNiagaraComponent->Deactivate();
	LoopedAudioComponent->Stop();
	SetActorEnableCollision(false);
	PlayExplodeEffects();
	GetWorldTimerManager().SetTimer(PreTeleportTimerHandle, this, &ARougeProjectileTeleport::DelayedTeleportTimeElapsed, DelayedTeleportTime);
}

void ARougeProjectileTeleport::DelayedTeleportTimeElapsed()
{
	AActor* Instigator = GetInstigator();
	
	check(Instigator);
	
	Instigator->TeleportTo(GetActorLocation(), GetInstigator()->GetActorRotation());
	
	Destroy();
}


void ARougeProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);
	
	StartDelayedTeleportation();
}
