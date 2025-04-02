// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BowlingFrame.h"
#include "BowlingScoreUIInterface.generated.h"

UINTERFACE(Blueprintable)
class UBowlingScoreUIInterface : public UInterface
{
    GENERATED_BODY()
};

class BOWLINGBASIC_API IBowlingScoreUIInterface
{
    GENERATED_BODY()

public:
    /// <summary>
    /// Funtion to update the Frame UI
    /// </summary>
    /// <param name="NewFrame">Frame Score</param>
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling")
    void UpdateScoreUI(const FBowlingFrame& NewFrame);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling")
    void UpdateIndex(int32 index);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling")
    void EnableEdit();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling")
    void DisableEdit();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling") 
    void ResetBoard();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling") 
    void ResetVisuals();
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling") 
    void UpdateScoreBoardVisuals(const TArray<FBowlingFrame>& Frames);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bowling") 
    void SwitchDelegates(bool bAddDynamic);

};
