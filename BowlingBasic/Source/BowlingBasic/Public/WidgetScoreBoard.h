// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BowlingScoreUIInterface.h"
#include "Blueprint/UserWidget.h"
#include "WidgetScoreBoard.generated.h"

class UHorizontalBox;
class UWidgetBowlingScore;
/**
 * 
 */
UCLASS()
class BOWLINGBASIC_API UWidgetScoreBoard : public UUserWidget ,public IBowlingScoreUIInterface
{
	GENERATED_BODY()
public:
	//Costruct widget
	virtual void NativeConstruct() override;
	void UpdateScoreBoardVisuals_Implementation(const TArray<FBowlingFrame>& Frames);
	void ResetBoard_Implementation();
	UFUNCTION()
	void ResetScoreBoard();
	UFUNCTION()
	void OnResetButtonReleased();
	UFUNCTION()
	void OnPlayerNameCommitted(const FText& Text, ETextCommit::Type CommitMethod);

private:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> BowlingScoreWidgetClass;
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* ScoreContainer;
	UPROPERTY()
	TArray<TScriptInterface<IBowlingScoreUIInterface>> FrameInterfaces;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResetButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* PlayerNameInput;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FinalScoreText;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* EditNamePanel;
};

