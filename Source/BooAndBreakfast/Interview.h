// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <list>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interview.generated.h"

UCLASS()
class BOOANDBREAKFAST_API AInterview : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterview();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintNativeEvent)
	void OnInterview();
	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> Interviews;
	UPROPERTY()
	AActor* Player;
	
private:
	float VolumeMultiplier;
	float StartTime;
	float PitchMultiplier;
};
