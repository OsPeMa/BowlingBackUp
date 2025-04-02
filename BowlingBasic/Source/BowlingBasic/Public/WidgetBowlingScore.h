// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BowlingScoreUIInterface.h"
#include "WidgetBowlingScore.generated.h"

/**
* Forward
*/
class UTextBlock;
class UComboBoxString;
/**
 * Widget that represents a single frame in the bowling scoreboard.
 * Handles user input, updates visual elements, and communicates with the GameMode.
 */
UCLASS()
class BOWLINGBASIC_API UWidgetBowlingScore : public UUserWidget , public IBowlingScoreUIInterface
{
	GENERATED_BODY()


	//Costruct widget
public:
	//Interfaces
	/** Adds or removes delegates from dropdown selection (used for safe updates) 
	*MUST AddDynamics when you finish your updates
	*/
	void SwitchDelegates_Implementation(bool bAddDynamic);
	/** Resets dropdowns, text, and score visuals */
	void ResetVisuals_Implementation();
	/** Enables dropdowns for user interaction */
	void EnableEdit_Implementation();
	/** Disables dropdowns to lock the frame */
	void DisableEdit_Implementation();
	/** Sets the current frame index and updates index label */
	void UpdateIndex_Implementation(int32 index);
	/** Populates the widget with frame data (e.g. strikes, spares, numeric throws) */
	void UpdateScoreUI_Implementation(const FBowlingFrame& NewFrame) ;

	
protected:
	//Constructor
	virtual void NativeConstruct() override;	
	//Update info on Gamemode
	void TrySendFrameToGame();
	//Delegates / UI Events
	UFUNCTION()
	void OnFirstRollChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void OnSecondRollChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void OnThirdRollChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	/**
	* VARIABLES TO SHOW TO THE Player
	*/
	/** Text showing the frame number (1-10) */
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 FrameIndex;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UTextBlock* FrameIndexText;

	/** ComboBox for first roll selection */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* FirstRollText;

	/** ComboBox for second roll selection */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* SecondRollText;

	/** ComboBox for third roll selection */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ThirdRollText;
	/** Text showing the score of this frame */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* FrameScoreText;
	//TODO depens on ScoreType a feedback on UI
	/** Score type (Strike, Spare, or Normal) */
	UPROPERTY(BlueprintReadOnly)
	EScoreType ScoreType;
};
