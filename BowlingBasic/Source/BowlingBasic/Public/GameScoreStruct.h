// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSession.generated.h"
#include "GameScoreStruct.generated.h"
//Struct that will help to serialize Scores
USTRUCT(BlueprintType)
struct FGameScoreStruct
{
	GENERATED_BODY()

    UPROPERTY()
    int32 Frame;

    UPROPERTY()
    int32 FirstThrow;

    UPROPERTY()
    int32 SecondThrow;

    UPROPERTY()
    int32 ThirdThrow;

    UPROPERTY()
    int32 Score;
};
//The Game data
USTRUCT(BlueprintType)
struct FGameSessionData
{
    GENERATED_BODY()

    UPROPERTY()
    FString PlayerName;

    UPROPERTY()
    TArray<FGameScoreStruct> Frames;

    UPROPERTY()
    int32 FinalScore;

    UPROPERTY()
    FString Date;
};