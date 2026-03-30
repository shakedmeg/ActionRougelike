// Fill out your copyright notice in the Description page of Project Settings.


#include "RougePickupActor.h"
#include "Components/SphereComponent.h"


ARougePickupActor::ARougePickupActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMeshComp"));
	RootComponent = PickupMeshComponent;
	PickupMeshComponent->SetCollisionProfileName("NoCollision");
	
	OverlapComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	OverlapComponent->SetupAttachment(PickupMeshComponent);
	OverlapComponent->SetSphereRadius(128.f);
	OverlapComponent->SetCollisionProfileName("Pickups");
}

void ARougePickupActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ARougePickupActor::OnActorOverlapped);
}

void ARougePickupActor::OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
