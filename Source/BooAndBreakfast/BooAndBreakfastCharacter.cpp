// Copyright Epic Games, Inc. All Rights Reserved.

#include "BooAndBreakfastCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Introduction.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ABooAndBreakfastCharacter

ABooAndBreakfastCharacter::ABooAndBreakfastCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ABooAndBreakfastCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////// Input

void ABooAndBreakfastCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABooAndBreakfastCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABooAndBreakfastCharacter::Look);
		EnhancedInputComponent->BindAction(RepeatAction, ETriggerEvent::Triggered, this, &ABooAndBreakfastCharacter::Repeat);
		EnhancedInputComponent->BindAction(ProceedAction, ETriggerEvent::Triggered, this, &ABooAndBreakfastCharacter::Proceed);
		EnhancedInputComponent->BindAction(LayTrapAction, ETriggerEvent::Triggered, this, &ABooAndBreakfastCharacter::Proceed);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
void ABooAndBreakfastCharacter::Repeat()
{
	if(Day)
	{
		if(FirstInterview)
		{
			Introduction->RepeatWithNothingToRepeat();
			return;
		}
		Introduction->RepeatLastInterview();
	}
	else
	{
		switch (CurrentRoom)
		{
		case 0:
			CurrentRoom = 2;
			TeleportTo(PositionsToTeleportTo[2], RotationsToTeleportTo[2]);
			break;
		case 1:
			--CurrentRoom;
			TeleportTo(PositionsToTeleportTo[0], RotationsToTeleportTo[0]);
			break;
		case 2:
			--CurrentRoom;
			TeleportTo(PositionsToTeleportTo[1], RotationsToTeleportTo[1]);
			break;
		default: ;
		}
	}
}
void ABooAndBreakfastCharacter::Proceed()
{
	if(Day)// Logik ligger ockso i introduction
	{
		if(CurrentCount >= CountToProceed)// Byt till natt
		{
			Day = false;
			CurrentCount = 0;
			TeleportTo(PositionsToTeleportTo[0], RotationsToTeleportTo[0]);
			return;
		}
		CurrentCount++;
		FirstInterview = false;
		Introduction->OnInterview();
	}
	else
	{
		switch (CurrentRoom)
		{
		case 0:
			++CurrentRoom;
			TeleportTo(PositionsToTeleportTo[1], RotationsToTeleportTo[1]);
			break;
		case 1:
			++CurrentRoom;
			TeleportTo(PositionsToTeleportTo[2], RotationsToTeleportTo[2]);
			break;
		case 2:
			CurrentRoom = 0;
			TeleportTo(PositionsToTeleportTo[0], RotationsToTeleportTo[0]);
			break;
		default: ;
		}
	}
}

void ABooAndBreakfastCharacter::LayTrap()
{
	if(!Day)
	{
		OnLayTrap();
	}
}

void ABooAndBreakfastCharacter::SetDay(bool NewDay)
{
	Day = NewDay;
}

void ABooAndBreakfastCharacter::Move(const FInputActionValue& Value)
{
	if(!Day)
	{
		// input is a Vector2D
		FVector2D MovementVector = Value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			// add movement 
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
			AddMovementInput(GetActorRightVector(), MovementVector.X);
		}
	}
}

void ABooAndBreakfastCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if(Day)
		{
			FRotator R = GetActorRotation();
			FRotator C = GetFirstPersonCameraComponent()->GetComponentRotation();
			// if(LookAxisVector.X >= 0)
			// {
			// 	if(GetActorRotation().Yaw < MaxYaw)
			// 	{
			// 		AddControllerYawInput(LookAxisVector.X);
			// 	}
			// }
			// if(LookAxisVector.X < 0)
			// {
			// 	if(GetActorRotation().Yaw > MinYaw)
			// 	{
			// 		AddControllerYawInput(LookAxisVector.X);
			// 	}
			// }
			// if(LookAxisVector.Y >= 0)
			// {
			// 	if(C.Pitch < MaxPitch)
			// 	{
			// 		AddControllerPitchInput(LookAxisVector.Y);
			// 	}
			// }
			// if(LookAxisVector.Y < 0)
			// {
			// 	if(C.Pitch > MinPitch)
			// 	{
			// 		AddControllerPitchInput(LookAxisVector.Y);
			// 	}
			// }
			if(R.Yaw + LookAxisVector.X <= MaxYaw && R.Yaw + LookAxisVector.X >= MinYaw)
			{
				AddControllerYawInput(LookAxisVector.X);
			}
			if(C.Pitch + LookAxisVector.Y <= MaxPitch && C.Pitch + LookAxisVector.X >= MinPitch)
			{
				AddControllerPitchInput(LookAxisVector.Y);
			}
			// if(GetActorRotation().Yaw >MaxYaw) 
			// {
			//     R.Yaw = MaxYaw;
			//     GetParentActor()->SetActorRotation(R);
			// }
			// if(GetActorRotation().Yaw < MinYaw)
			// {
			//     R.Yaw = MinYaw;
			//     GetParentActor()->SetActorRotation(R);
			// }
		}
		else
		{
			AddControllerYawInput(LookAxisVector.X);
		}
	}
}