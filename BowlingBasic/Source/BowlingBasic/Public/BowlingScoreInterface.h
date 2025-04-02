// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BowlingFrame.h"
#include "BowlingScoreInterface.generated.h"

UINTERFACE(Blueprintable)
class UBowlingScoreInterface : public UInterface
{
    GENERATED_BODY()
};

class BOWLINGBASIC_API IBowlingScoreInterface
{
    GENERATED_BODY()

public:
    virtual int GetCurrentScore_Implementation() const = 0;
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling")
    int32 AddNewFrame(const FBowlingFrame& NewFrame);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling")
    void UpdateScore();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling")
    void ResetGame();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling")
    void FinishGame();
};