// Fill out your copyright notice in the Description page of Project Settings.


#include "Interview.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AInterview::AInterview()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInterview::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInterview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInterview::OnInterview_Implementation()
{
	UGameplayStatics::PlaySound2D(this, Interviews[0], VolumeMultiplier,  PitchMultiplier,  StartTime);
}



