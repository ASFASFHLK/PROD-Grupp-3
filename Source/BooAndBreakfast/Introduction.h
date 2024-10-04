// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Introduction.generated.h"

class ABooAndBreakfastCharacter;

UCLASS()
class BOOANDBREAKFAST_API AIntroduction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIntroduction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintNativeEvent)
	void OnInterview();
	UFUNCTION()
	void RepeatLastInterview();
	UFUNCTION()
	void RepeatWithNothingToRepeat();
	UFUNCTION()
	void SelectInterview();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* NothingToRepeat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USoundWave*> Interviews;
	UPROPERTY()
	AActor* Player;
	UPROPERTY()
	int32 InterviewSelector = 0;
	UPROPERTY()
	int32 WhichInterview;
	UPROPERTY()
	int32 NumberOfInterviews = 2;
	UPROPERTY()
	int32 CurrentInterview = 0;
	UPROPERTY()
	bool Tutorial = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABooAndBreakfastCharacter* PlayerCharacter;	

};
