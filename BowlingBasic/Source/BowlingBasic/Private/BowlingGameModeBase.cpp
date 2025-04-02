// Fill out your copyright notice in the Description page of Project Settings.


#include "BowlingGameModeBase.h"
#include "Misc/Paths.h"
#include "BowlingFrame.h"
#include "Engine/Engine.h"
#include "GameScoreStruct.h"
#include "Misc/FileHelper.h"
#include "WidgetScoreBoard.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "BowlingScoreUIInterface.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

// Called at game start
void ABowlingGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (ScoreBoardClass)
    {
        ScoreBoardWidget = CreateWidget<UUserWidget>(GetWorld(), ScoreBoardClass);
        if (ScoreBoardWidget)
        {
            ScoreBoardWidget->AddToViewport();
        }
    }
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeUIOnly());
    }
}

// Updates score using interface once new frame is added
int32 ABowlingGameModeBase::AddNewFrame_Implementation(const FBowlingFrame& NewFrame)
{
    int32 temp = -1;
    if (NewFrame.FrameIndex == Frames.Num()) {

         temp = AddFrame(NewFrame.FirstThrow, NewFrame.SecondThrow, NewFrame.ThirdThrow);

        if (ScoreBoardWidget && ScoreBoardWidget->GetClass()->ImplementsInterface(UBowlingScoreUIInterface::StaticClass()))
        {
            IBowlingScoreUIInterface::Execute_UpdateScoreBoardVisuals(ScoreBoardWidget, Frames);
        }
        SetRound(Frames.Num());
    }
    return temp;
}

// Constructor sets expected frame capacity
ABowlingGameModeBase::ABowlingGameModeBase()
{
    Frames.Reserve(10);
}

// Adds a new frame to the list
int32 ABowlingGameModeBase::AddFrame(int FirstThrow, int SecondThrow, int ThirdThrow)
{
    if (Frames.Num() < 10)
    {
        int32 Index = -1;
        if (Frames.Num() == 9)
        {
            Index = Frames.Add(FBowlingFrame(FirstThrow, SecondThrow, ThirdThrow, Frames.Num()));
        }
        else
        {
            Index = Frames.Add(FBowlingFrame(FirstThrow, SecondThrow, Frames.Num()));
        }
        SetRound(Frames.Num());
        CalculateScore();
        return Index;
    }
    return -1;
}

int32 ABowlingGameModeBase::GetCurrentRound() const
{
    return CurrentRound;
}

void ABowlingGameModeBase::SetRound(int32 newRound) 
{
    CurrentRound = newRound;
    
}

// Calculates total score including bonuses from strikes and spares
int ABowlingGameModeBase::CalculateScore()
{
    TotalScore = 0;

    for (int i = 0; i < Frames.Num(); i++)
    {
        const FBowlingFrame& Current = Frames[i];

        if (i == 9)
        {
            TotalScore += Current.FirstThrow + Current.SecondThrow + Current.ThirdThrow;
        }
        else
        {
            TotalScore += Current.FirstThrow + Current.SecondThrow;

            if (Current.ScoreType == EScoreType::EST_Spare && i + 1 < Frames.Num())
            {
                TotalScore += Frames[i + 1].FirstThrow;
            }
            else if (Current.ScoreType == EScoreType::EST_Strike && i + 1 < Frames.Num())
            {
                const FBowlingFrame& Next = Frames[i + 1];
                TotalScore += Next.FirstThrow;
                if (Next.ScoreType == EScoreType::EST_Strike && i + 2 < Frames.Num())
                {
                    TotalScore += Frames[i + 2].FirstThrow;
                }
                else
                {
                    TotalScore += Next.SecondThrow;
                }
            }
        }

        Frames[i].ProcessedScore = TotalScore;
    }

    return TotalScore;
}

void ABowlingGameModeBase::SaveSessionAsJson()
{
    FGameSessionData Session;
    Session.PlayerName = IBowlingScoreUIInterface::Execute_GetPlayerName(ScoreBoardWidget);
    Session.FinalScore = TotalScore;
    Session.Date = FDateTime::UtcNow().ToString();

    for (int32 i = 0; i < Frames.Num(); i++)
    {
        FGameScoreStruct F;
        F.Frame = i + 1;
        F.FirstThrow = Frames[i].FirstThrow;
        F.SecondThrow = Frames[i].SecondThrow;
        F.ThirdThrow = Frames[i].ThirdThrow;
        F.Score = Frames[i].ProcessedScore;

        Session.Frames.Add(F);
    }

    FString OutputString;
    FJsonObjectConverter::UStructToJsonObjectString(Session, OutputString);

    FFileHelper::SaveStringToFile(
        OutputString,
        *(FPaths::ProjectSavedDir() + TEXT("LastGame.json"))
    );
}

// Prints the current score to the log (debug only)
void ABowlingGameModeBase::PrintScore()
{
    int Score = CalculateScore();
    UE_LOG(LogTemp, Warning, TEXT("Puntaje total: %d"), Score);
}

// Gets total score via interface
int32 ABowlingGameModeBase::GetCurrentScore_Implementation() const
{
    return TotalScore;
}

// Clears all game state and notifies UI to reset
void ABowlingGameModeBase::ResetGame_Implementation()
{
    Frames.Empty();

    if (ScoreBoardWidget && ScoreBoardWidget->GetClass()->ImplementsInterface(UBowlingScoreUIInterface::StaticClass()))
    {
        IBowlingScoreUIInterface::Execute_ResetBoard(ScoreBoardWidget);
    }
    TotalScore = 0;
}

void ABowlingGameModeBase::FinishGame_Implementation()
{
    SaveSessionAsJson();
}
