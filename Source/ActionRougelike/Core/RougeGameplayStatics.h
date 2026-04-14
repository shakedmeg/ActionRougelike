// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RougeGameplayStatics.generated.h"

class URougeActionSystemComponent;
/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API URougeGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	static bool IsFullHealth(URougeActionSystemComponent* ActionComp);
};
