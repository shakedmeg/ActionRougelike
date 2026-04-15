// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "RougeActionSystemComponent.generated.h"

struct FRougeAttribute;
struct FGameplayTag;
class URougeAction;
class URougeAttributeSet;

UENUM(BlueprintType)
enum EAttributeModifyType
{
	Base,
	Modifier,
	OverrideBase,
	Invalid
};

// Native C++ delegate
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayTag /*AttributeTag*/, float /*NewAttributeValue*/, float /*OldAttributeValue*/);
// Blueprint delegate
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnAttributeDynamicChanged, FGameplayTag, AttributeTag, float, NewAttributeValue, float, OldAttributeValue);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROUGELIKE_API URougeActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	URougeActionSystemComponent();
	
	void StartAction(FGameplayTag InActionName);
	void StopAction(FGameplayTag InActionName);
	
	UFUNCTION(BlueprintCallable)
	void ApplyAttributeChange(FGameplayTag AttributeTag, float Delta, EAttributeModifyType ModifyType);
	
	FRougeAttribute* GetAttribute(FGameplayTag InAttributeTag) const;
	
	UFUNCTION(BlueprintCallable)
	float GetAttributeValue(FGameplayTag InAttributeTag) const;
	
	FOnAttributeChanged& GetAttributeListener(FGameplayTag InAttributeTag);
	
	UFUNCTION(BlueprintCallable, DisplayName="Add Attribute Listener", meta = (Keywords="events,delegate"))
	void AddDynamicAttributeListener(FOnAttributeDynamicChanged Event, FGameplayTag AttributeTag);
	
	virtual void InitializeComponent() override;

	void GrantAction(TSubclassOf<URougeAction> NewActionClass);
	
	FGameplayTagContainer ActiveGameplayTags;
	
	virtual void BeginPlay() override;

protected:
	
	UPROPERTY()
	TObjectPtr<URougeAttributeSet> Attributes;
	
	TMap<FGameplayTag, FRougeAttribute*> CachedAttributes;
	
	UPROPERTY(EditAnywhere, Category = Attributes, NoClear)
	TSubclassOf<URougeAttributeSet> AttributeSetClass;
	
	TMap<FGameplayTag, FOnAttributeChanged> AttributeListeners;
	
	TMap<FGameplayTag, TArray<FOnAttributeDynamicChanged>> AttributeDynamicListeners;
	
	UPROPERTY()
	TArray<TObjectPtr<URougeAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<URougeAction>> DefaultActions;
};
