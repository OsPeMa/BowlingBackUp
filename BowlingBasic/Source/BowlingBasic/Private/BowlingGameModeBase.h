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
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UWidgetScoreBoard> ScoreBoardClass;
    
    UPROPERTY()
    TArray<FBowlingFrame> Frames;
    
    UPROPERTY()
    int32 TotalScore;

    UPROPERTY()
    UUserWidget* ScoreBoardWidget;

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Bowling")
    int CalculateScore();
public:

    //Interface
    virtual int GetCurrentScore_Implementation() const override;
    virtual int32 AddNewFrame_Implementation(const FBowlingFrame& NewFrame) override;
    virtual void ResetGame_Implementation() override;

    //Constructor
    ABowlingGameModeBase();
    //add a frame 
    UFUNCTION(BlueprintCallable, Category = "Bowling")
    int32 AddFrame(int FirstThrow, int SecondThrow, int ThirdThrow);

    //Debug
    UFUNCTION(BlueprintCallable, Category = "Bowling")
    void PrintScore();
};
