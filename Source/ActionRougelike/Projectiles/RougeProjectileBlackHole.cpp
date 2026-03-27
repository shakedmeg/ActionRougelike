// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeProjectileBlackHole.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARougeProjectileBlackHole::ARougeProjectileBlackHole()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->Radius = 800.f;
	RadialForceComponent->ForceStrength = -800000.f;
	
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	SphereComponent->SetSphereRadius(20.0f);
	SphereComponent->SetCollisionProfileName("BlackholeCore");
	
	ProjectileMovementComponent->InitialSpeed = 500.0f;
	InitialLifeSpan = 5.f;
}

void ARougeProjectileBlackHole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARougeProjectileBlackHole::OnSphereOverlappedActor);
}

void ARougeProjectileBlackHole::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,                                                                                                                                                                                                          
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{                                                                                                                                                                                                                                                                                                                
	if (OtherComp->IsSimulatingPhysics())
	{                                                                                                                                                                                                                                                                                                            
		OtherActor->Destroy();
	}                                                                                                                                                                                                                                                                                                            
}           