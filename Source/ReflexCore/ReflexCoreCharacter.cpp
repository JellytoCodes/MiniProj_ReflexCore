// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReflexCoreCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "ReflexHUDWidget.h"
#include "TargetDummy.h"
#include "TextDisplayActor.h"
#include "HitManager.h"
#include "GameManager.h"
#include "ReflexCoreGameMode.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AReflexCoreCharacter::AReflexCoreCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));

}

void AReflexCoreCharacter::BeginPlay()
{
	Super::BeginPlay();

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(Mesh1P, AttachmentRules, FName(TEXT("GripPoint")));

	
	if(reflexHUDWidgetClass)
	{
		reflexHUDWidgetInstance = CreateWidget<UReflexHUDWidget>(GetWorld(), reflexHUDWidgetClass);
		reflexHUDWidgetInstance->AddToViewport();
	}

	FindTextDisplayActor();

	hitManagerInstance = NewObject<UHitManager>();
	hitManagerInstance->Init(scoreDisplayActor, accuracyDisplayActor);

	gameMode = Cast<AReflexCoreGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

//////////////////////////////////////////////////////////////////////////// Input

void AReflexCoreCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AReflexCoreCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AReflexCoreCharacter::Look);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AReflexCoreCharacter::Fire);
	}
}

void AReflexCoreCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AReflexCoreCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AReflexCoreCharacter::Fire()
{
	FVector startLocation = FirstPersonCameraComponent->GetComponentLocation();
	FVector endLocation = FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector() * 5000;

	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startLocation, endLocation, ECC_Visibility, params);

	bIsHitTarget = false;
	FireMotion(bHit, hitInfo);
	
	HitTargetActor(bHit, hitInfo);
	HitTextActor(bHit, hitInfo);

	if(gameMode->GetGameManager()->IsGameActive()) hitManagerInstance->ProcessHit(bIsHitTarget);
}

void AReflexCoreCharacter::FindTextDisplayActor()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATextDisplayActor::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		ATextDisplayActor* TextActor = Cast<ATextDisplayActor>(Actor);
		if (TextActor && TextActor->GetDisplayCategory() == ETextDisplayCategory::score)
		{
			scoreDisplayActor = TextActor;
		}
		else if (TextActor && TextActor->GetDisplayCategory() == ETextDisplayCategory::accuracyRate)
		{
			accuracyDisplayActor = TextActor;
		}
	}
}

void AReflexCoreCharacter::FireMotion(bool bHit, FHitResult hitInfo)
{	
	if(!bHit) return;

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireAnimation != nullptr)
	{
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AReflexCoreCharacter::HitTargetActor(bool bHit, FHitResult hitInfo)
{
	if(!bHit) return;

	auto* target = hitInfo.GetActor();
	if(!target) return;

	auto* targetActor = Cast<ATargetDummy>(target);
	if(targetActor) 
	{
		bIsHitTarget = true;
		targetActor->TargetDestroy();
	}
}

void AReflexCoreCharacter::HitTextActor(bool bHit, FHitResult hitInfo)
{
	if(!bHit && bIsHitTarget) return;

	UPrimitiveComponent* hitComp = hitInfo.GetComponent();
	if(!hitComp) return;

	AActor* ownerActor = hitComp->GetOwner();
	if(!ownerActor) return;

	if(ATextDisplayActor* TextActor = Cast<ATextDisplayActor>(ownerActor))
	{
		if(gameMode)
		{
			switch(TextActor->GetDisplayCategory())
			{
				case ETextDisplayCategory::difficulty :
				break;

				case ETextDisplayCategory::startMode :
					gameMode->GetGameManager()->StartGame();
					hitManagerInstance->HitTextDisplay();
					hitManagerInstance->ResetStats();
				break;

				case ETextDisplayCategory::endMode :
					gameMode->GetGameManager()->EndGame();
					hitManagerInstance->HitTextDisplay();
				break;

				case ETextDisplayCategory::restartMode :
					gameMode->GetGameManager()->RestartGame();
					hitManagerInstance->ResetStats();
				break;

				case ETextDisplayCategory::quitMode :
					gameMode->GetGameManager()->QuitGame();
				break; 
			}
		}
	}
}
