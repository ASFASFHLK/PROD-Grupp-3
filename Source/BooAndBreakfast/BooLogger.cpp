// Fill out your copyright notice in the Description page of Project Settings.


#include "BooLogger.h"
#include <chrono>

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
	GetWorldTimerManager().SetTimer(StartTimer, this, &ABooLogger::StartingLogs, 2.0f);
}

void ABooLogger::StartingLogs()
{
	SingleLogEntry("Starting new game-------------------");
}

void ABooLogger::SingleLogEntry(FString Text)
{
	FString File = FPaths::ProjectConfigDir();
	File.Append(TEXT("ActionLog.txt"));
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	auto end = std::chrono::system_clock::now();

	
	std::time_t EndTime = std::chrono::system_clock::to_time_t(end);
	char* Temp = std::ctime(&EndTime);
	FString TimeString(Temp);
	FString FileContent;
	
	if (FileManager.FileExists(*File))
	{
		// We use the LoadFileToString to load the file into
		if(!FFileHelper::LoadFileToString(FileContent,*File,FFileHelper::EHashOptions::None))
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Did not load text from file"));
			return;
		}	
		FString TextToSave = FileContent + "#" + Text + ", Date: " + TimeString;
		if(!FFileHelper::SaveStringToFile(TextToSave,*File))
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Failed to write FString to file."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: ERROR: Can not read the file because it was not found."));
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Expected file location: %s"),*File);
	}	
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

void ABooLogger::StartLog()
{
	FString File = FPaths::ProjectConfigDir();
	File.Append(TEXT("MyConfig.txt"));
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FString StringToWrite(TEXT("Hello World. Written from Unreal Engine 4"));
	if (FileManager.FileExists(*File))
	{
		// We use the LoadFileToString to load the file into
		if(!FFileHelper::SaveStringToFile(StringToWrite,*File))
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Failed to write FString to file."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: ERROR: Can not read the file because it was not found."));
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Expected file location: %s"),*File);
	}	
}

