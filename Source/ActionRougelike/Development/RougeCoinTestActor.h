// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RougeCoinTestActor.generated.h"

UCLASS()
class ACTIONROUGELIKE_API ARougeCoinTestActor : public AActor
{
	GENERATED_BODY()

public:
	
	ARougeCoinTestActor();
	
	UFUNCTION(BlueprintCallable)
	void SpawnCoins(int32 SpawnCount);
	
protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<USceneComponent> DefaultSceneComponent;
};
