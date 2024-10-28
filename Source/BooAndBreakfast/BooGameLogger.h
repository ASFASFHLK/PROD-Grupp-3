// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BooGameLogger.generated.h"

UCLASS()
class BOOANDBREAKFAST_API ABooGameLogger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABooGameLogger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void Log(FString Text);


private:
	UFUNCTION()
	void OnBeginLog();

};
