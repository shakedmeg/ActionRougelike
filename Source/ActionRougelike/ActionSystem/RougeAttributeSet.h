// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RougeAttributeSet.generated.h"

class URougeActionSystemComponent;

USTRUCT()
struct FRougeAttribute
{
	GENERATED_BODY()
	
	FRougeAttribute() {}
	
	FRougeAttribute(float InBase) 
		: Base(InBase) {}
	
	UPROPERTY(EditAnywhere)
	float Base = 0.0f;
	
	UPROPERTY(Transient)
	float Modifier = 0.0f;
	
	float GetValue()
	{
		return Base + Modifier;
	}
};


/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API URougeAttributeSet : public UObject
{
	GENERATED_BODY()

public:
	
	URougeActionSystemComponent* GetOwningComponent() const;
	
	virtual void InitializeAttributes() {};
	
	virtual void PostAttributeChanged() {};
};


UCLASS()
class URougeHealthAttributeSet : public URougeAttributeSet
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category = Attributes)
	FRougeAttribute Health;
	
	UPROPERTY(EditAnywhere, Category = Attributes)
	FRougeAttribute MaxHealth;
	
	virtual void PostAttributeChanged() override;
	
	URougeHealthAttributeSet();
	
};

UCLASS()
class URougePawnAttributeSet : public URougeHealthAttributeSet
{
	GENERATED_BODY()

public:
	
	// Walking speed directly linked with Character Movement Component
	UPROPERTY(EditAnywhere, Category = Attributes)
	FRougeAttribute MoveSpeed;
	
	virtual void InitializeAttributes();
	
	virtual void PostAttributeChanged() override;
	
	void ApplyMoveSpeed();
	
	URougePawnAttributeSet();
	
};

UCLASS()
class URougePlayerAttributeSet : public URougePawnAttributeSet
{
	GENERATED_BODY()
};


UCLASS()
class URougeMonsterAttributeSet : public URougePawnAttributeSet
{
	GENERATED_BODY()
	
public:
	URougeMonsterAttributeSet();
};
