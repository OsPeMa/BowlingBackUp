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
 * Custom GameMode for managing bowling logic, score calculation, and session saving.
 */
UCLASS()
class ABowlingGameModeBase : public AGameModeBase , public IBowlingScoreInterface
{
	GENERATED_BODY()
protected:

    /** Widget class to spawn as the scoreboard */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UWidgetScoreBoard> ScoreBoardClass;
    /** Bowling frames (up to 10) */
    UPROPERTY()
    TArray<FBowlingFrame> Frames;
    /** Total accumulated score */
    UPROPERTY()
    int32 TotalScore;
    /** Current scoreboard UI widget */
    UPROPERTY()
    UUserWidget* ScoreBoardWidget;
    /** Current Game round */
    UPROPERTY()
    int32 CurrentRound;


    /** Called when game starts, creates scoreboard and enables mouse */
    virtual void BeginPlay() override;
    /** Calculates the cumulative bowling score across frames */
    UFUNCTION(BlueprintCallable, Category = "Bowling")
    int CalculateScore();
    /** Serializes the session to JSON for saving */
    void SaveSessionAsJson();


public:
    UFUNCTION(BlueprintCallable, Category = "Bowling")
    void SetRound(int32 newRound);




    //Interface
    /** Returns the final score */
    virtual int32 GetCurrentScore_Implementation() const;
    /** Inserts a frame directly into the data array */
    virtual int32 AddNewFrame_Implementation(const FBowlingFrame& NewFrame) override;
    /** Clears current session and notifies UI to reset */
    virtual void ResetGame_Implementation() override;
    /** Finalizes game and triggers data export */
    void FinishGame_Implementation();



    /** Constructor that pre-allocates frame array */
    ABowlingGameModeBase();


    //add a frame 
    UFUNCTION(BlueprintCallable, Category = "Bowling")
    int32 AddFrame(int FirstThrow, int SecondThrow, int ThirdThrow); 

    UFUNCTION(BlueprintCallable, Category = "Bowling")
    int32 GetCurrentRound()const;
    /** Utility function to log the score to output log */
    UFUNCTION(BlueprintCallable, Category = "Bowling")
    void PrintScore();
};
