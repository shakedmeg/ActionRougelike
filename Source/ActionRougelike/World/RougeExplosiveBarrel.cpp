// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeExplosiveBarrel.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
ARougeExplosiveBarrel::ARougeExplosiveBarrel()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionProfileName("PhysicsActor");
	RootComponent = MeshComponent;
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(MeshComponent);
	RadialForceComponent->Radius = 750.f;
	RadialForceComponent->ImpulseStrength = 150000.f;
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = true;

}

float ARougeExplosiveBarrel::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	bool bShouldSkipTimer = GetWorldTimerManager().IsTimerActive(ExplosionTimerHandle) || bDidExplode;
	if (bShouldSkipTimer)
	{
		return Damage;
	}
	
	ActiveBurningEffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(BurningEffect, MeshComponent, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	ActiveBurningSoundComp = UGameplayStatics::SpawnSoundAttached(LoopedBurningSound, MeshComponent);

	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ARougeExplosiveBarrel::Explode, ExplosionDelay);
	
	return Damage;
}

void ARougeExplosiveBarrel::Explode()
{
	bDidExplode = true;

	if (ActiveBurningEffectComp)
	{
		ActiveBurningEffectComp->Deactivate();
	}
	
	if (ActiveBurningSoundComp)
	{
		ActiveBurningSoundComp->Stop();
	}
	
	
	RadialForceComponent->FireImpulse();
	
	MeshComponent->AddImpulse(FVector::UpVector * 1000, NAME_None, true);
	MeshComponent->AddAngularImpulseInDegrees(FVector::RightVector * 1000, NAME_None, true);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
}
