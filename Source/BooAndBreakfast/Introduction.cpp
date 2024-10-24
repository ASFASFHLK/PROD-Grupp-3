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
	if(BossAudio)
	{
		BossAudio->Stop();
	}
	BossResponse = FMath::RandRange(0,3);
	BossAudio = UGameplayStatics::SpawnSound2D(this, BossIntroduction, 1,1, 0);
}

void AIntroduction::RepeatLastInterview()
{
	if(BossAudio)
	{
		if(Tutorial)
		{
			BossAudio->Stop();
			BossAudio = UGameplayStatics::SpawnSound2D(this, BossIntroduction, 1,1, 0);
		}
		else
		{
			BossAudio = UGameplayStatics::SpawnSound2D(this, BossResponses[BossResponse], 1,1, 0);
		}
	}
}
void AIntroduction::OnBeginDay()
{
	BossAudio = UGameplayStatics::SpawnSound2D(this, BossIntroduction, 1,1, 0);
}
void AIntroduction::OnInterview_Implementation()
{
	if(GetWorldTimerManager().TimerExists(StartTimer))
	{
		GetWorldTimerManager().ClearTimer(StartTimer);
	}
	if(BossAudio)
	{
		BossAudio->Stop();
	}
	Tutorial = false;
	PlayerCharacter->SwitchToNight();
}



// old stuff


// void AIntroduction::RepeatLastInterview()
// {
// 	if(FirstInterview)
// 	{
// 		RepeatWithNothingToRepeat();
// 		return;
// 	}
// 	if(Tutorial)
// 	{
// 		UGameplayStatics::PlaySound2D(this, Interviews[TutorialSelector]);
// 		return;
// 	}// could break
// 	UGameplayStatics::PlaySound2D(this, Interviews[WhichInterview * 4 + InterviewSelector]);
// }
// void AIntroduction::RepeatWithNothingToRepeat()
// {
// 	UGameplayStatics::PlaySound2D(this, NothingToRepeat);
// }
//
// void AIntroduction::SelectInterview()
// {
// 	WhichInterview = FMath::RandRange(1,3);
// }
//
//
//
// void AIntroduction::OnInterview_Implementation()
// {
// 	FirstInterview = false;
// 	if(TutorialSelector >= 3)
// 	{
// 		Tutorial = false;
// 	}
// 	if(Tutorial)
// 	{
// 		UGameplayStatics::PlaySound2D(this, Interviews[++TutorialSelector]);
// 		return;
// 	}
// 	if(InterviewSelector >= 3)
// 	{
// 		SelectInterview();
// 		InterviewSelector = -1;
// 		if(CurrentInterview++ >= NumberOfInterviews)
// 		{
// 			PlayerCharacter->SwitchToNight();
// 		}
// 	}
// 	UGameplayStatics::PlaySound2D(this, Interviews[WhichInterview * 4 + ++InterviewSelector]);
// }

