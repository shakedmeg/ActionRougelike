// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeAction_ProjectileAttack.h"

#include "NiagaraFunctionLibrary.h"
#include "RougeActionSystemComponent.h"
#include "RougeGameTypes.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/RougeProjectile.h"


TAutoConsoleVariable<float> CVarProjectileAdjustmentDebugDraw(TEXT("game.projectile.DebugDraw"), 0.0f,
	TEXT("Enable projectile aim adjustment debug rendering. (0 = off, > 0 is duration)"),
	ECVF_Cheat);


URougeAction_ProjectileAttack::URougeAction_ProjectileAttack()
{
	MuzzleSocketName = "Muzzle_01";
}

void URougeAction_ProjectileAttack::StartAction_Implementation()
{
	Super::StartAction_Implementation();
	
	URougeActionSystemComponent* ActionComp = GetOwningComponent();
	ACharacter* Character = CastChecked<ACharacter>(ActionComp->GetOwner());
	
	Character->PlayAnimMontage(AttackMontage);
	
	FTimerHandle AttackTimerHandle;
	
	const float AttackDelayTime = 0.2f;
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, Character->GetMesh(), MuzzleSocketName,
	FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	
	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ThisClass::AttackTimerElapsed, AttackDelayTime, false);
}


void URougeAction_ProjectileAttack::AttackTimerElapsed()
{
	URougeActionSystemComponent* ActionComp = GetOwningComponent();
	ACharacter* Character = CastChecked<ACharacter>(ActionComp->GetOwner());
	
	FVector SpawnLocation = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Character;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	FVector EyeLocation;
	FRotator EyeRotation;
	
	Character->GetController()->GetPlayerViewPoint(EyeLocation, EyeRotation);
	
	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 5000.f);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Character);
	
	UWorld* World = GetWorld();
	
	FVector AdjustedTargetLocation;
	FHitResult Hit;
	if (World->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, COLLISION_PROJECTILE, QueryParams))
	{
		AdjustedTargetLocation = Hit.Location;
	}
	else
	{
		AdjustedTargetLocation = TraceEnd;
	}
	
	FRotator SpawnRotation = (AdjustedTargetLocation - SpawnLocation).Rotation();;
	
	AActor* NewProjectile = World->SpawnActor<ARougeProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	Character->MoveIgnoreActorAdd(NewProjectile);

#if !UE_BUILD_SHIPPING	
	float DebugDrawDuration = CVarProjectileAdjustmentDebugDraw.GetValueOnGameThread();
	if (DebugDrawDuration > 0.0f)
	{
		// The hit location or trace end
		DrawDebugBox(World, AdjustedTargetLocation, FVector(20.f), FColor::Green, false, DebugDrawDuration);
		
		// Adjustment line trace
		DrawDebugLine(World, EyeLocation, TraceEnd, FColor::Green, false, DebugDrawDuration);
		
		// New projectile path
		DrawDebugLine(World, SpawnLocation, AdjustedTargetLocation, FColor::Yellow, false, DebugDrawDuration);
		
		// The original path of the projectile
		DrawDebugLine(World, SpawnLocation, SpawnLocation + EyeRotation.Vector() * 5000.0f, FColor::Purple, false, DebugDrawDuration);
	}
#endif
}
