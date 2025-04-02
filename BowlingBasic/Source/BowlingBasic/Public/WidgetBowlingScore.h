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
 * Class
 */
UCLASS()
class BOWLINGBASIC_API UWidgetBowlingScore : public UUserWidget , public IBowlingScoreUIInterface
{
	GENERATED_BODY()


	//Costruct widget
public:
	//Interfaces
	void SwitchDelegates_Implementation(bool bAddDynamic);
	void ResetVisuals_Implementation();
	void EnableEdit_Implementation();
	void DisableEdit_Implementation();
	void UpdateIndex_Implementation(int32 index);
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
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 FrameIndex;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UTextBlock* FrameIndexText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* FirstRollText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* SecondRollText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ThirdRollText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* FrameScoreText;
	//TODO depens on ScoreType a feedback on UI
	UPROPERTY(BlueprintReadOnly)
	EScoreType ScoreType;
};
