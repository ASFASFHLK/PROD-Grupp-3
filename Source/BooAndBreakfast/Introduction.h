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
	// UFUNCTION()
	// void RepeatWithNothingToRepeat();
	// UFUNCTION()
	// void SelectInterview();
	UFUNCTION()
	void OnBeginDay();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* NothingToRepeat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* BossIntroduction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USoundWave*> Interviews;
	
private:
	
	UPROPERTY()
	FTimerHandle StartTimer;
	UPROPERTY()
	UAudioComponent* BossAudio;
	UPROPERTY()
	AActor* Player;
	UPROPERTY()
	int32 InterviewSelector = -1;
	UPROPERTY()
	int32 TutorialSelector = -1;
	UPROPERTY()
	int32 WhichInterview;
	UPROPERTY()
	int32 NumberOfInterviews = 1;
	UPROPERTY()
	int32 CurrentInterview = 0;
	UPROPERTY()
	bool Tutorial = true;
	UPROPERTY()
	bool FirstInterview = true;
	UPROPERTY()
	ABooAndBreakfastCharacter* PlayerCharacter;	

};
