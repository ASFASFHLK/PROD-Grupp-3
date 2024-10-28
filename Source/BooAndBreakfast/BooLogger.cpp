// Fill out your copyright notice in the Description page of Project Settings.


#include "BooLogger.h"

// Sets default values
ABooLogger::ABooLogger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABooLogger::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle StartTimer;
	GetWorldTimerManager().SetTimer(StartTimer, this, &ABooLogger::Log, 2.0f);
}

// Called every frame
void ABooLogger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABooLogger::Log()
{
	FString File = FPaths::ProjectConfigDir();
	File.Append(TEXT("ActionLog.txt"));
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FString FileContent;
	if(FileManager.FileExists(*File))
	{
		if(FFileHelper::LoadFileToString(FileContent, *File, FFileHelper::EHashOptions::None))
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Text from File: %s"), *FileContent);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load text from file"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("File not loaded at %s"), *File);
	}
}

