// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeBTTask_RangedAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Projectiles/RougeProjectile.h"


URougeBTTask_RangedAttack::URougeBTTask_RangedAttack()
{
	TargetActorKey.SelectedKeyName = NAME_TargetActor;
}


EBTNodeResult::Type URougeBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* Character = Cast<ACharacter> (OwnerComp.GetAIOwner()->GetPawn());
	check(Character);
	
	FVector SpawnLocation = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);
	
	AActor* TargetActor = Cast<AActor> (OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (!IsValid(TargetActor))
	{
		return EBTNodeResult::Failed;
	}
	
	
	FVector Direction = TargetActor->GetActorLocation() - SpawnLocation;
	
	FRotator SpawnRotation = Direction.Rotation();
	
	SpawnRotation.Pitch += FMath::FRandRange(0.0f, MaxBulletSpread);
	SpawnRotation.Yaw += FMath::FRandRange(-MaxBulletSpread, MaxBulletSpread);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Character;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	return NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
