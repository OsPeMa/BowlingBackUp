// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetScoreBoard.h"
#include "WidgetBowlingScore.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "BowlingScoreInterface.h"


#pragma region DELEGATES
void UWidgetScoreBoard::OnResetButtonReleased()
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
        if (GM && GM->GetClass()->ImplementsInterface(UBowlingScoreInterface::StaticClass()))
        {
            IBowlingScoreInterface::Execute_ResetGame(GM);
        }
    }
    if (EditNamePanel)
    {
        EditNamePanel->SetVisibility(ESlateVisibility::Visible);
    }

    if (PlayerNameInput)
    {
        const FString InputName = PlayerNameInput->GetText().ToString();
        if (!InputName.IsEmpty() && PlayerNameText)
        {
            PlayerNameText->SetText(FText::FromString(InputName));
        }
        
    }
}

void UWidgetScoreBoard::OnPlayerNameCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
    if (PlayerNameInput && PlayerNameText)
    {
        PlayerNameText->SetText(PlayerNameInput->GetText());
        if (EditNamePanel)EditNamePanel->SetVisibility(ESlateVisibility::Collapsed);
    }
}

#pragma endregion

void UWidgetScoreBoard::NativeConstruct()
{

    Super::NativeConstruct();

    if (PlayerNameText)
    {
        PlayerNameText->SetText(FText::FromString("Jugador 1"));
    }

    if (ResetButton)
    {
        ResetButton->OnReleased.AddDynamic(this, &UWidgetScoreBoard::OnResetButtonReleased);
    }

    if (BowlingScoreWidgetClass && ScoreContainer) 
    {
        for (int i = ScoreContainer->GetChildrenCount(); i < 10; i++)
        {
            UUserWidget* NewScoreWidget = CreateWidget<UUserWidget>(this,BowlingScoreWidgetClass);
            if (NewScoreWidget && NewScoreWidget->GetClass()->ImplementsInterface(UBowlingScoreUIInterface::StaticClass()))
            {
                UPanelSlot* PanelSlot = ScoreContainer->AddChild(NewScoreWidget);
                
                if (UHorizontalBoxSlot* HBoxSlot = Cast<UHorizontalBoxSlot>(PanelSlot))
                {
                    HBoxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill)); 
                    HBoxSlot->SetPadding(FMargin(1.5f)); 
                }
                Execute_UpdateIndex(NewScoreWidget, i);
                //FrameInterfaces.Add(NewScoreWidget);
                FrameInterfaces.AddUnique(NewScoreWidget);
            }
        }
        if (FrameInterfaces[0])Execute_EnableEdit(FrameInterfaces[0].GetObject());
    }

    if (EditNamePanel)
        EditNamePanel->SetVisibility(ESlateVisibility::Visible);
    if(PlayerNameInput)
        PlayerNameInput->OnTextCommitted.AddDynamic(this, &UWidgetScoreBoard::OnPlayerNameCommitted);
    if (FinalScoreText)
        FinalScoreText->SetText(FText::FromString("0"));
    
}

void UWidgetScoreBoard::UpdateScoreBoardVisuals_Implementation(const TArray<FBowlingFrame>& Frames)
{
    //Update frame UI Info
    for (int i = 0; i < Frames.Num(); i++) {
        FrameInterfaces[i]->Execute_UpdateScoreUI(FrameInterfaces[i].GetObject(), Frames[i]);
        IBowlingScoreUIInterface::Execute_DisableEdit(FrameInterfaces[i].GetObject());
    }
    //Activate next frame
    if (FrameInterfaces.IsValidIndex(Frames.Num())) 
    {
        IBowlingScoreUIInterface::Execute_EnableEdit(FrameInterfaces[Frames.Num()].GetObject());
    }
    //UpdateFinalScore
    if(FinalScoreText)
    {
        int FinalScore = Frames.Last().ProcessedScore;
        FinalScoreText->SetText(FText::AsNumber(FinalScore));
    }
    //Colapse Player input name
    if (EditNamePanel) {
        EditNamePanel->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UWidgetScoreBoard::ResetBoard_Implementation()
{
    ResetScoreBoard();
}

FString UWidgetScoreBoard::GetPlayerName_Implementation() const
{
    if (PlayerNameText)return PlayerNameText->GetText().ToString();;
    return "\0";
}

void UWidgetScoreBoard::UpdateScoreUI_Implementation(const FBowlingFrame& NewFrame)
{
}

void UWidgetScoreBoard::ResetScoreBoard()
{

    for (int i = 0; i < FrameInterfaces.Num(); i++)
    {
        if (FrameInterfaces[i].GetObject())
        {
            IBowlingScoreUIInterface::Execute_ResetVisuals(FrameInterfaces[i].GetObject());
            IBowlingScoreUIInterface::Execute_DisableEdit(FrameInterfaces[i].GetObject());
        }

    }
    if (FrameInterfaces[0])Execute_EnableEdit(FrameInterfaces[0].GetObject());

    if (FinalScoreText)
    {
        FinalScoreText->SetText(FText::FromString("0"));
    }

    if (PlayerNameText && PlayerNameInput)
    {
        const FString InputName = PlayerNameInput->GetText().ToString();
        PlayerNameText->SetText(FText::FromString(InputName.IsEmpty() ? TEXT("Jugador 1") : InputName));
    }
    if (EditNamePanel)
    {
        EditNamePanel->SetVisibility(ESlateVisibility::Visible);
    }
}