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
		EnhancedInputComponent->BindAction(LayTrapAction, ETriggerEvent::Triggered, this, &ABooAndBreakfastCharacter::LayTrap);
		EnhancedInputComponent->BindAction(Teleport1Action, ETriggerEvent::Triggered, this, &ABooAndBreakfastCharacter::TeleportOne);
		EnhancedInputComponent->BindAction(Teleport2Action, ETriggerEvent::Triggered, this, &ABooAndBreakfastCharacter::TeleportTwo);
		EnhancedInputComponent->BindAction(Teleport3Action, ETriggerEvent::Triggered, this, &ABooAndBreakfastCharacter::TeleportThree);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
void ABooAndBreakfastCharacter::Repeat()
{
	if(Introduction->GetTutorial())
	{
		if(TryTutorialInput(1))
		{
			TutorialProgress();
			return;
		}
	}
	if(Day)
	{
		Introduction->RepeatLastInterview();
	}
	// else
	// {
	// 	switch (CurrentRoom)
	// 	{
	// 	case 0:
	// 		CurrentRoom = 2;
	// 		TeleportTo(PositionsToTeleportTo[2], RotationsToTeleportTo[2]);
	// 		break;
	// 	case 1:
	// 		--CurrentRoom;
	// 		TeleportTo(PositionsToTeleportTo[0], RotationsToTeleportTo[0]);
	// 		break;
	// 	case 2:
	// 		--CurrentRoom;
	// 		TeleportTo(PositionsToTeleportTo[1], RotationsToTeleportTo[1]);
	// 		break;
	// 	default: ;
	// 	}
	// }
}
void ABooAndBreakfastCharacter::Proceed()
{
	if(Introduction->GetTutorial())
	{
		if(TryTutorialInput(0))
		{
			TutorialProgress();
			return;
		}
	}
	if(Day)
	{
		Introduction->OnInterview();
	}
	// else
	// {
	// 	switch (CurrentRoom)
	// 	{
	// 	case 0:
	// 		++CurrentRoom;
	// 		TeleportTo(PositionsToTeleportTo[1], RotationsToTeleportTo[1]);
	// 		break;
	// 	case 1:
	// 		++CurrentRoom;
	// 		TeleportTo(PositionsToTeleportTo[2], RotationsToTeleportTo[2]);
	// 		break;
	// 	case 2:
	// 		CurrentRoom = 0;
	// 		TeleportTo(PositionsToTeleportTo[0], RotationsToTeleportTo[0]);
	// 		break;
	// 	default: ;
	// 	}
	// }
}

void ABooAndBreakfastCharacter::LayTrap()
{
	if(Introduction->GetTutorial())
	{
		if(TryTutorialInput(5))
		{
			TutorialProgress();
			return;
		}
	}
	if(!Day)
	{
		OnLayTrap();
	}
}

void ABooAndBreakfastCharacter::SetDay(bool NewDay)
{
	Day = NewDay;
}

void ABooAndBreakfastCharacter::TeleportOne()
{
	if(Introduction->GetTutorial())
	{
		if(TryTutorialInput(2))
		{
			TutorialProgress();
			return;
		}
	}
	if(!Day)
 	{
		OnTeleported(1);
		TeleportTo(PositionsToTeleportTo[0], RotationsToTeleportTo[0]);
 	}
}

void ABooAndBreakfastCharacter::TeleportTwo()
{
	if(Introduction->GetTutorial())
	{
		if(TryTutorialInput(3))
		{
			TutorialProgress();
			return;
		}
	}
	if(!Day)
 	{
		OnTeleported(2);
		TeleportTo(PositionsToTeleportTo[1], RotationsToTeleportTo[1]);
 	}
}

void ABooAndBreakfastCharacter::TeleportThree()
{
	if(Introduction->GetTutorial())
	{
		if(TryTutorialInput(4))
		{
			TutorialProgress();
			return;
		}
	}
	if(!Day)
 	{
		OnTeleported(3);
		TeleportTo(PositionsToTeleportTo[2], RotationsToTeleportTo[2]);
 	}
}


void ABooAndBreakfastCharacter::SwitchToNight()
{
	SetDay(false);
	CurrentRoom = 0;
	FRotator C = GetFirstPersonCameraComponent()->GetComponentRotation();
	float CPitchInput = -C.Pitch;
	// UE_LOG(LogTemp, Display, TEXT("Pitch before = %f, PitchInput = %f"), C.Pitch, CPitchInput);
	// AddControllerPitchInput(CPitchInput);
	// float CPitchT = GetFirstPersonCameraComponent()->GetComponentTransform().Rotator().Pitch;
	// UE_LOG(LogTemp, Display, TEXT("Pitch after = %f, PitchInput = %f"), C.Pitch, CPitchInput);
	// FRotator TempRotator = RotationsToTeleportTo[0];
	// TempRotator.Pitch = CPitchInput;
	TeleportTo(PositionsToTeleportTo[0], RotationsToTeleportTo[0]);
}

void ABooAndBreakfastCharacter::SwitchToDay()
{
	SetDay(true);
	TeleportTo(PositionsToTeleportTo[3], RotationsToTeleportTo[3]);
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
			FRotator C = GetFirstPersonCameraComponent()->GetComponentRotation();
			if(LookAxisVector.X >= 0)
			{
				if(GetActorRotation().Yaw < MaxYaw)
				{
					AddControllerYawInput(LookAxisVector.X);
				}
			}
			if(LookAxisVector.X < 0)
			{
				if(GetActorRotation().Yaw > MinYaw)
				{
					AddControllerYawInput(LookAxisVector.X);
				}
			}
		}
		else
		{
			AddControllerYawInput(LookAxisVector.X);
		}
	}
}
bool ABooAndBreakfastCharacter::TryTutorialInput(int Input)
{
	return TutorialSections[Input];
}

void ABooAndBreakfastCharacter::TutorialProgress()
{
	for(int i = 0; i < TutorialSections.Num(); ++i)
	{
		if(TutorialSections[i] == true)
		{
			if(i < TutorialSections.Num() - 1)
			{
				TutorialSections[i] = false;
				TutorialSections[i + 1] = true;
				break;
			}
			else
			{
				Introduction->SetTutorial(false);
			}
		}
	}
}
