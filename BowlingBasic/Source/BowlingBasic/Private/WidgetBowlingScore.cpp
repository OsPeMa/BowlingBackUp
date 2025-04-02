// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetBowlingScore.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxString.h"
#include "BowlingScoreInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

void UWidgetBowlingScore::NativeConstruct()
{
	Super::NativeConstruct();
    if (FirstRollText && SecondRollText && ThirdRollText)
    {
        FirstRollText->ClearOptions();
        for (int i = 0; i < 11; i++)
        {
            FirstRollText->AddOption(FString::FromInt(i));
        }

        FirstRollText->OnSelectionChanged.AddDynamic(this, &UWidgetBowlingScore::OnFirstRollChanged);
        SecondRollText->OnSelectionChanged.AddDynamic(this, &UWidgetBowlingScore::OnSecondRollChanged);
        ThirdRollText->OnSelectionChanged.AddDynamic(this, &UWidgetBowlingScore::OnThirdRollChanged);
    }
	
}

void UWidgetBowlingScore::OnFirstRollChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    IBowlingScoreUIInterface::Execute_SwitchDelegates(this, false);
    int FirstThrow = FCString::Atoi(*SelectedItem);
    
    if (SecondRollText)
    {
        SecondRollText->ClearOptions();
        int MaxSecond = (FirstThrow == 10) ? (FrameIndex != 9) ? 0 : 10 : (10 - FirstThrow);
        for (int i = 0; i <= MaxSecond; i++)
        {
            SecondRollText->AddOption(FString::FromInt(i));
        } 
        if (FirstThrow == 10 && FrameIndex != 9)
        {
            SecondRollText->SetSelectedIndex(0);  
            TrySendFrameToGame();
            FirstRollText->SetIsEnabled(false);
            SecondRollText->SetIsEnabled(false);
            ThirdRollText->SetIsEnabled(false);
        }
    }
    if (FrameIndex == 9 && FirstThrow == 10 && ThirdRollText)
    {
        ThirdRollText->SetVisibility(ESlateVisibility::Visible);

        ThirdRollText->ClearOptions();
        for (int i = 0; i <= 10; i++)
        {
            ThirdRollText->AddOption(FString::FromInt(i));
        }
    }
    else if (ThirdRollText && FrameIndex == 9)
    {
        ThirdRollText->SetVisibility(ESlateVisibility::Collapsed);
    }

    IBowlingScoreUIInterface::Execute_SwitchDelegates(this, true);
}

void UWidgetBowlingScore::OnSecondRollChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    IBowlingScoreUIInterface::Execute_SwitchDelegates(this, false);
    if(FrameIndex !=9)
        TrySendFrameToGame();
    else
    {
        int First = FCString::Atoi(*FirstRollText->GetSelectedOption());
        int Second = FCString::Atoi(*SecondRollText->GetSelectedOption());

        bool bStrike = (First == 10);
        bool bSpare = (!bStrike && (First + Second == 10));

        if (bStrike || bSpare)
        {
            if (ThirdRollText)
            {
                ThirdRollText->SetVisibility(ESlateVisibility::Visible);
                ThirdRollText->ClearOptions();

                for (int i = 0; i <= 10; i++)
                {
                    ThirdRollText->AddOption(FString::FromInt(i));
                }

             
                if (!ThirdRollText->GetSelectedOption().IsEmpty())
                {
                    TrySendFrameToGame(); 
                }
            }
        }
        else
        {
           
            TrySendFrameToGame();
        }
    }
    IBowlingScoreUIInterface::Execute_SwitchDelegates(this, true);
}

void UWidgetBowlingScore::OnThirdRollChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    IBowlingScoreUIInterface::Execute_SwitchDelegates(this, false);
    TrySendFrameToGame();
    IBowlingScoreUIInterface::Execute_SwitchDelegates(this, true);
}

void UWidgetBowlingScore::SwitchDelegates_Implementation(bool bAddDynamic)
{
    if (bAddDynamic) 
    {
        FirstRollText->OnSelectionChanged.AddDynamic(this, &UWidgetBowlingScore::OnFirstRollChanged);
        SecondRollText->OnSelectionChanged.AddDynamic(this, &UWidgetBowlingScore::OnSecondRollChanged);
        ThirdRollText->OnSelectionChanged.AddDynamic(this, &UWidgetBowlingScore::OnThirdRollChanged);
    }
    else
    {
        FirstRollText->OnSelectionChanged.RemoveDynamic(this, &UWidgetBowlingScore::OnFirstRollChanged);
        SecondRollText->OnSelectionChanged.RemoveDynamic(this, &UWidgetBowlingScore::OnSecondRollChanged);
        ThirdRollText->OnSelectionChanged.RemoveDynamic(this, &UWidgetBowlingScore::OnThirdRollChanged);
    }
}

void UWidgetBowlingScore::ResetVisuals_Implementation()
{   
    IBowlingScoreUIInterface::Execute_SwitchDelegates(this, false);
    IBowlingScoreUIInterface::Execute_UpdateScoreUI(this,FBowlingFrame());
    if (FirstRollText && SecondRollText && ThirdRollText) 
    {
        FirstRollText->ClearOptions();
        FirstRollText->SetSelectedOption(" ");
        for (int i = 0; i < 11; i++)
        {
            FirstRollText->AddOption(FString::FromInt(i));
        }
        SecondRollText->ClearOptions();
        SecondRollText->SetSelectedOption(" ");
        ThirdRollText->ClearOptions();
        ThirdRollText->SetSelectedOption(" ");
    }
    if (FrameScoreText) 
    {
        FrameScoreText->SetText(FText::FromString("0"));
    }
    IBowlingScoreUIInterface::Execute_SwitchDelegates(this, true);
}

void UWidgetBowlingScore::TrySendFrameToGame()
{
    if (!FirstRollText || !SecondRollText || !ThirdRollText) return;

    FString FirstOpt = FirstRollText->GetSelectedOption();
    FString SecondOpt = SecondRollText->GetSelectedOption();
    FString ThirdOpt = ThirdRollText->GetSelectedOption();

    if (!FirstOpt.IsNumeric() || !SecondOpt.IsNumeric()) return;

    int First = FCString::Atoi(*FirstOpt);
    int Second = FCString::Atoi(*SecondOpt);
    int Third = 0;

    if (ThirdRollText->GetVisibility() == ESlateVisibility::Visible && ThirdOpt.IsNumeric())
    {
        Third = FCString::Atoi(*ThirdOpt);
    }

    FBowlingFrame NewFrame(First, Second, Third, FrameIndex); // Dummy index

    UObject* GameMode = Cast<UObject>(UGameplayStatics::GetGameMode(this));
    if (GameMode && GameMode->GetClass()->ImplementsInterface(UBowlingScoreInterface::StaticClass()))
    {
        UE_LOG(LogTemp, Display, TEXT("Enviando frame: %d, %d, %d"), First, Second, Third);
        IBowlingScoreInterface::Execute_AddNewFrame(GameMode, NewFrame);
        
        if(FrameIndex==9)IBowlingScoreInterface::Execute_FinishGame(GameMode);
    }
}


void UWidgetBowlingScore::EnableEdit_Implementation()
{
    FirstRollText->SetIsEnabled(true);
    SecondRollText->SetIsEnabled(true);
    ThirdRollText->SetIsEnabled(true);
}

void UWidgetBowlingScore::DisableEdit_Implementation()
{
    FirstRollText->SetIsEnabled(false);
    SecondRollText->SetIsEnabled(false);
    ThirdRollText->SetIsEnabled(false);
}

void UWidgetBowlingScore::UpdateIndex_Implementation(int32 index)
{
    FrameIndex = index;
    if (FrameIndexText)
    {
        FrameIndexText->SetText(FText::FromString(FString::Printf(TEXT("%d"), index+1)));
    }
}

void UWidgetBowlingScore::UpdateScoreUI_Implementation(const FBowlingFrame& NewFrame)
{
    if (FirstRollText)
    {
        if (NewFrame.FirstThrow == 10)
        {
            FirstRollText->AddOption("X");
            FirstRollText->SetSelectedOption("X");
        }
        else
        {
            FirstRollText->SetSelectedOption(FString::FromInt(NewFrame.FirstThrow));
        }
    }

    if (SecondRollText)
    {
        if (NewFrame.ScoreType == EScoreType::EST_Spare)
        {
            SecondRollText->AddOption( "/" );
            SecondRollText->SetSelectedOption( "/" );
        }
        else if (NewFrame.FirstThrow == 10)
        {
            SecondRollText->SetSelectedOption(" ");
        }
        else
        {
            SecondRollText->SetSelectedOption(FString::FromInt(NewFrame.SecondThrow));
        }
        if (NewFrame.FrameIndex == 9 && NewFrame.SecondThrow == 10)
        {
            SecondRollText->AddOption("X");
            SecondRollText->SetSelectedOption( "X");
        }
    }

    if (ThirdRollText)
    {
        if (NewFrame.FrameIndex == 9)
        {
            ThirdRollText->SetVisibility(ESlateVisibility::Visible);
            if (NewFrame.ThirdThrow == 10)
            {

                ThirdRollText->AddOption("X");
                ThirdRollText->SetSelectedOption("X");
            }
            else
            {
                ThirdRollText->SetSelectedOption(FString::FromInt(NewFrame.ThirdThrow));
            }
        }
        else
        {
            ThirdRollText->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

    if (FrameScoreText)
    {
        FrameScoreText->SetText(FText::AsNumber(NewFrame.ProcessedScore));
    }

    ScoreType = NewFrame.ScoreType;

}
