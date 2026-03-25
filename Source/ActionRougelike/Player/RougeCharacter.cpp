// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "RougePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/RougeProjectileMagic.h"


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
	
	MuzzleSocketName = "Muzzle_01";
}

// Called when the game starts or when spawned

void ARougePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ARougePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARougePlayerCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ARougePlayerCharacter::Look);
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &ARougePlayerCharacter::PrimaryAttack);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ARougePlayerCharacter::Jump);
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

void ARougePlayerCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackMontage);
	
	FTimerHandle AttackTimerHandle;
	
	const float AttackDelayTime = 0.2f;
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	
	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ARougePlayerCharacter::AttackTimerElapsed, AttackDelayTime);
}

void ARougePlayerCharacter::AttackTimerElapsed()
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotation = GetControlRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AActor* NewProjectile = GetWorld()->SpawnActor<ARougeProjectileMagic>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	MoveIgnoreActorAdd(NewProjectile);
}

// Called every frame
void ARougePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}