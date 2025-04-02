// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BowlingFrame.generated.h"
UENUM()
enum class EScoreType : uint8
{
	EST_None UMETA(DisplayName = "Default"),
	EST_Normal UMETA(DisplayName = "Normal Throw"),
	EST_Spare UMETA(DisplayName = "Spare Throw"),
	EST_Strike UMETA(DisplayName = "Strike Throw")
};

/**
 * Represents a single bowling frame, including its throws and score state.
 */
USTRUCT(BlueprintType)
struct BOWLINGBASIC_API FBowlingFrame
{
	GENERATED_BODY()
public:
	/** Frame's position in the game (0-based index) */
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 FrameIndex;
	/** First roll in the frame */
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 FirstThrow;
	/** Second roll in the frame */
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 SecondThrow;
	/** Third roll (only used in 10th frame if strike/spare) */
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 ThirdThrow;
	/** Calculated score for the frame (sum of throws) */
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 FrameScore;	
	/** Cumulative score at the end of this frame */
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 ProcessedScore;
	/** Type of scoring this frame represents */
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	EScoreType ScoreType = EScoreType::EST_Normal;

	/** Default constructor initializes everything to zero */
	FBowlingFrame();
	/** Destructor */
	~FBowlingFrame();
	/** Constructor for standard frames (1st to 9th) */
	FBowlingFrame(int first, int second, int index);
	/** Constructor for 10th frame with optional third throw */
	FBowlingFrame(int first, int second, int third, int index);
};
