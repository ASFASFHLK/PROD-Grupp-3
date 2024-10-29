// Fill out your copyright notice in the Description page of Project Settings.


#include "BooGameLogger.h"
#include "chrono"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABooGameLogger::ABooGameLogger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABooGameLogger::BeginPlay()
{
	Super::BeginPlay();
	OnBeginLog();
	
}

void ABooGameLogger::Log(FString Text)
{
 	FString File = FPaths::ProjectConfigDir();
 	File.Append(TEXT("ActionLog.txt"));
 	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
    const std::chrono::time_point End = std::chrono::system_clock::now();


    const std::time_t EndTime = std::chrono::system_clock::to_time_t(End);
 	char* Temp = std::ctime(&EndTime);
    const FString TimeString(Temp);

    if (FileManager.FileExists(*File))
 	{
	    FString FileContent;
	    // We use the LoadFileToString to load the file into
 		if(!FFileHelper::LoadFileToString(FileContent,*File,FFileHelper::EHashOptions::None))
 		{
 			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Did not load text from file"));
 			return;
 		}
	    const FString TextToSave = FileContent + "#" + Text + ", Date: " + TimeString;
 		if(!FFileHelper::SaveStringToFile(TextToSave,*File))
 		{
 			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Failed to write FString to file."));
 		}
 	}
 	else
 	{
 		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: ERROR: Can not read the file because it was not found."));
 		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Expected file location: %s"),*File);
 		UKismetSystemLibrary::PrintString(this, *File, true); 
 	}
}

void ABooGameLogger::OnBeginLog()
{
}


