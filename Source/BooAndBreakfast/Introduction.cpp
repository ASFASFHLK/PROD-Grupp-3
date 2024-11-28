// Fill out your copyright notice in the Description page of Project Settings.


#include "Introduction.h"

#include "BooAndBreakfastCharacter.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIntroduction::AIntroduction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIntroduction::BeginPlay()
{
	Super::BeginPlay();
	// SelectInterview();

	GetWorldTimerManager().SetTimer(StartTimer, this, &AIntroduction::OnBeginDay, 1.0f);
}

// Called every frame
void AIntroduction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIntroduction::OnSwitchToNight_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("SwitchToNightIntroduction"));
	// if(BossAudio)
	// {
	// 	BossAudio->Stop();
	// }
	// BossResponse = FMath::RandRange(0,3);
	// LastSoundMade = BossResponses[BossResponse];
	// BossAudio = UGameplayStatics::SpawnSound2D(this, BossResponses[BossResponse], 1,1, 0);
}

// void AIntroduction::RepeatLastInterview()
// {
// 	if(BossAudio)
// 	{
// 		if(Tutorial)
// 		{
// 			BossAudio->Stop();
// 			BossAudio = UGameplayStatics::SpawnSound2D(this, BossIntroduction, 1,1, 0);
// 		}
// 		else
// 		{
// 			BossAudio = UGameplayStatics::SpawnSound2D(this, BossResponses[BossResponse], 1,1, 0);
// 		}
// 	}
// }
void AIntroduction::OnBeginDay()
{
	SelectInterview();
	// BossAudio = UGameplayStatics::SpawnSound2D(this, BossIntroduction, 1,1, 0);
}

void AIntroduction::PlaySound(TArray<USoundWave*> Sounds)
{
	if(BossAudio)
	{
		BossAudio->Stop();
	}
	int32 ResponseTemp = FMath::RandRange(0, Sounds.Num() - 1);
	LastSoundMade = Sounds[ResponseTemp];
	BossAudio = UGameplayStatics::SpawnSound2D(this, Sounds[ResponseTemp], 1,1, 0);
}

void AIntroduction::PlayWrongSound(USoundWave* Sound)
{
	if(BossAudio)
 	{
 		BossAudio->Stop();
 	}
 	BossAudio = UGameplayStatics::SpawnSound2D(this, Sound, 1,1, 0);
}

bool AIntroduction::GetTutorial() const
{
	return Tutorial;
}

void AIntroduction::SetTutorial(const bool NewValue)
{
	Tutorial = NewValue;
}


// void AIntroduction::OnInterview_Implementation()
// {
// 	if(GetWorldTimerManager().TimerExists(StartTimer))
// 	{
// 		GetWorldTimerManager().ClearTimer(StartTimer);
// 	}
// 	if(BossAudio)
// 	{
// 		BossAudio->Stop();
// 	}
// 	Tutorial = false;
// 	PlayerCharacter->SwitchToNight();
// }



// old stuff


void AIntroduction::RepeatLastInterview()
{
	UE_LOG(LogTemp, Display, TEXT("RepeatLastInterview"));
	if(BossAudio)
	{
		BossAudio->Stop();
	}
	if(!LastSoundMade)
	{
		RepeatWithNothingToRepeat();
		return;
	}
	BossAudio = UGameplayStatics::SpawnSound2D(this, LastSoundMade);
	// if(Tutorial)
	// {
	// 	BossAudio = UGameplayStatics::SpawnSound2D(this, Interviews[TutorialSelector]);
	// 	return;
	// }// could break
	// BossAudio = UGameplayStatics::SpawnSound2D(this, Interviews[WhichInterview * 4 + InterviewSelector]);
}
void AIntroduction::RepeatWithNothingToRepeat()
{
	LastSoundMade = NothingToRepeat;
	BossAudio = UGameplayStatics::SpawnSound2D(this, NothingToRepeat);
}

void AIntroduction::SelectInterview()
{
	WhichInterview = FMath::RandRange(1,3);
}

void AIntroduction::OnInterview_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("Interview"));
	if(GetWorldTimerManager().TimerExists(StartTimer))
	{
		GetWorldTimerManager().ClearTimer(StartTimer);
	}
	if(BossAudio)
	{
		BossAudio->Stop();
	}
	PlayInterview();
}

void AIntroduction::PlayInterview()
{
	if(InterviewSelector >= 3)
	{
		SelectInterview();
		InterviewSelector = -1;
		if(CurrentInterview++ >= NumberOfInterviews)
		{
			PlayerCharacter->SwitchToNight();
			return;
		}
	}
	LastSoundMade = Interviews[WhichInterview * 4 + ++InterviewSelector];
	BossAudio = UGameplayStatics::SpawnSound2D(this, Interviews[WhichInterview * 4 + InterviewSelector]);
}

// void AIntroduction::PlayTutorial()
// {
// 		LastSoundMade = Interviews[++TutorialSelector];
// 		BossAudio = UGameplayStatics::SpawnSound2D(this, Interviews[++TutorialSelector]);
// }
