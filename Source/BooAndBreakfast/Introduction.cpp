// Fill out your copyright notice in the Description page of Project Settings.


#include "Introduction.h"

#include "BooAndBreakfastCharacter.h"
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
	SelectInterview();
	
}

// Called every frame
void AIntroduction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AIntroduction::RepeatLastInterview()
{
	if(FirstInterview)
	{
		RepeatWithNothingToRepeat();
		return;
	}
	if(Tutorial)
	{
		UGameplayStatics::PlaySound2D(this, Interviews[TutorialSelector]);
		return;
	}// could break
	UGameplayStatics::PlaySound2D(this, Interviews[WhichInterview * 4 + InterviewSelector]);
}

void AIntroduction::RepeatWithNothingToRepeat()
{
	UGameplayStatics::PlaySound2D(this, NothingToRepeat);
}

void AIntroduction::SelectInterview()
{
	WhichInterview = FMath::RandRange(1,3);
}

void AIntroduction::OnInterview_Implementation()
{
	FirstInterview = false;
	if(TutorialSelector >= 3)
	{
		Tutorial = false;
	}
	if(Tutorial)
	{
		UGameplayStatics::PlaySound2D(this, Interviews[++TutorialSelector]);
		return;
	}
	if(InterviewSelector >= 3)
	{
		SelectInterview();
		InterviewSelector = -1;
		if(CurrentInterview++ >= NumberOfInterviews)
		{
			PlayerCharacter->SwitchToNight();
		}
	}
	UGameplayStatics::PlaySound2D(this, Interviews[WhichInterview * 4 + ++InterviewSelector]);
}

