// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BowlingScoreInterface.h"
#include "WidgetBowlingScore.h"
#include "GameFramework/GameModeBase.h"
#include "BowlingGameModeBase.generated.h"
/**
* Forward
*/
class UWidgetScoreBoard;
/**
 * Class
 */
UCLASS()
class ABowlingGameModeBase : public AGameModeBase , public IBowlingScoreInterface
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UWidgetScoreBoard> ScoreBoardClass;
private:
    UPROPERTY()
    TArray<FBowlingFrame> Frames;
    UPROPERTY()
    int32 TotalScore;

    UPROPERTY()
    UUserWidget* ScoreBoardWidget;

public:

    virtual void BeginPlay() override;

    virtual int GetCurrentScore_Implementation() const override;
    virtual int32 AddNewFrame_Implementation(const FBowlingFrame& NewFrame) override;
    virtual void ResetGame_Implementation() override;
    /// <summary>
    /// DefaultConstructor
    /// </summary>
    ABowlingGameModeBase();
    /// <summary>
    /// Add score to array frames
    /// </summary>
    /// <param name="FirstThrow">fell pines</param>
    /// <param name="SecondThrow">fell pines</param>
    UFUNCTION(BlueprintCallable, Category = "Bowling")
    int32 AddFrame(int FirstThrow, int SecondThrow, int ThirdThrow);
    /// <summary>
    /// Calculate scores with bowling rules
    /// </summary>
    /// <returns>Total Score</returns>
    UFUNCTION(BlueprintCallable, Category = "Bowling")
    int CalculateScore();
    /// <summary>
    /// Debug print on console
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = "Bowling")
    void PrintScore();
};
