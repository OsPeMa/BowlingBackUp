// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BowlingScoreUIInterface.h"
#include "Blueprint/UserWidget.h"
#include "WidgetScoreBoard.generated.h"

class UHorizontalBox;
class UWidgetBowlingScore;

/**
 * Widget representing the full 10-frame scoreboard
 */
UCLASS()
class BOWLINGBASIC_API UWidgetScoreBoard : public UUserWidget ,public IBowlingScoreUIInterface
{
	GENERATED_BODY()
public:

	//interfaces
	/** Updates score UI for all frames and final score */
	void UpdateScoreBoardVisuals_Implementation(const TArray<FBowlingFrame>& Frames);
	/** Clears all visual data and resets the scoreboard */
	void ResetBoard_Implementation();
	/** Returns the player's current display name */
	virtual FString GetPlayerName_Implementation() const override;
	void UpdateScoreUI_Implementation(const FBowlingFrame& NewFrame);


protected:
	/** Called at widget construction, binds UI and spawns frame widgets */
	virtual void NativeConstruct() override;
	/** Resets all widget data and prepares a new game visually */
	UFUNCTION()
	void ResetScoreBoard();
	/** Triggered when the reset button is pressed */
	UFUNCTION()
	void OnResetButtonReleased();
	/** Triggered when player commits a name input (enter key or loss of focus) */
	UFUNCTION()
	void OnPlayerNameCommitted(const FText& Text, ETextCommit::Type CommitMethod);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> BowlingScoreWidgetClass;
	/** Container that holds all the 10 frame widgets */
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* ScoreContainer;
	/** UI button to start/reset game */
	UPROPERTY(meta = (BindWidget))
	class UButton* ResetButton;
	/** Input box for entering player name */
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* PlayerNameInput;
	/** Displays the current player name */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerNameText;
	/** Displays the final total score */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FinalScoreText;
	/** Panel that contains player name input (shown only at start/reset) */
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* EditNamePanel;
private:
	/** List of all frame widgets implementing the score UI interface */
	UPROPERTY()
	TArray<TScriptInterface<IBowlingScoreUIInterface>> FrameInterfaces;
};

