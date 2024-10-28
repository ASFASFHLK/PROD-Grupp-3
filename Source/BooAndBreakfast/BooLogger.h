// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BooLogger.generated.h"

UCLASS()
class BOOANDBREAKFAST_API ABooLogger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABooLogger();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void StartLog();
	UFUNCTION()
	void SingleLogEntry(FString Text);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void StartingLogs();

};
