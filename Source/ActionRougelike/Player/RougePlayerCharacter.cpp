// Fill out your copyright notice in the Description page of Project Settings.


#include "RougePlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "SharedGameplayTags.h"
#include "ActionSystem/RougeActionSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ARougePlayerCharacter::ARougePlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	ActionSystemComponent = CreateDefaultSubobject<URougeActionSystemComponent>(TEXT("ActionSystemComp"));
}

// Called to bind functionality to input
void ARougePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARougePlayerCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ARougePlayerCharacter::Look);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ARougePlayerCharacter::Jump);
	EnhancedInput->BindAction(Input_Sprint, ETriggerEvent::Started, this, &ARougePlayerCharacter::StartAction, SharedGameplayTag::Action_Sprint.GetTag());
	EnhancedInput->BindAction(Input_Sprint, ETriggerEvent::Completed, this, &ARougePlayerCharacter::StopAction, SharedGameplayTag::Action_Sprint.GetTag());
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &ARougePlayerCharacter::StartAction, SharedGameplayTag::Action_PrimaryAttack.GetTag());
	EnhancedInput->BindAction(Input_SecondaryAttack, ETriggerEvent::Triggered, this, &ARougePlayerCharacter::StartAction, SharedGameplayTag::Action_SecondaryAttack.GetTag());
	EnhancedInput->BindAction(Input_SpecialAttack, ETriggerEvent::Triggered, this, &ARougePlayerCharacter::StartAction, SharedGameplayTag::Action_SpecialAttack.GetTag());
}

float ARougePlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	ActionSystemComponent->ApplyAttributeChange(SharedGameplayTag::Attribute_Health, -ActualDamage, Base);
	float RageToAdd = DamageAmount * 0.75f;
	ActionSystemComponent->ApplyAttributeChange(SharedGameplayTag::Attribute_Rage, RageToAdd, Modifier);
	
	return ActualDamage;
}

void ARougePlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	FOnAttributeChanged& Event =  ActionSystemComponent->GetAttributeListener(SharedGameplayTag::Attribute_Health);
	Event.AddUObject(this, &ThisClass::OnHealthChanged);
}

void ARougePlayerCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D InputValue = InValue.Get<FVector2D>();
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	
	// Forward/Back
	AddMovementInput(ControlRot.Vector(), InputValue.X);
	
	// Sideways
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
}

void ARougePlayerCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();
	
	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void ARougePlayerCharacter::StartAction(FGameplayTag InActionName)
{
	ActionSystemComponent->StartAction(InActionName);
}

void ARougePlayerCharacter::StopAction(FGameplayTag InActionName)
{
	ActionSystemComponent->StopAction(InActionName);
}

void ARougePlayerCharacter::OnHealthChanged(FGameplayTag AttributeTag, float NewHealth, float OldHealth)
{
	if (FMath::IsNearlyZero(NewHealth))
	{
		DisableInput(nullptr);
		
		GetMovementComponent()->StopMovementImmediately();
		
		PlayAnimMontage(DeathMontage);
	}
}
