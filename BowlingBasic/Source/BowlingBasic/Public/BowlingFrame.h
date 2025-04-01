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
 * Struct
 */
USTRUCT(BlueprintType)
struct BOWLINGBASIC_API FBowlingFrame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 FrameIndex;
	/// <summary>
	/// How many pines fell down with first throw.
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 FirstThrow;
	/// <summary>
	/// How many pines fell down with second throw.
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 SecondThrow;
	/// <summary>
	/// How many pines fell down with third throw.
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 ThirdThrow;
	/// <summary>
	/// How many pines fell down.
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 FrameScore;	
	/// <summary>
	/// Sumatory until frame index
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	int32 ProcessedScore;

	UPROPERTY(BlueprintReadWrite, Category = "Bowling")
	EScoreType ScoreType = EScoreType::EST_Normal;

	/// <summary>
	/// Default constructor
	/// </summary>
	FBowlingFrame();
	/// <summary>
	/// Default Deconstructor
	/// </summary>
	~FBowlingFrame();
	/// <summary>
	/// Build up a frame with first and second values
	/// </summary>
	/// <param name="first">: First Throw Pine</param>
	/// <param name="second">: Second Throw Pine</param>
	FBowlingFrame(int first, int second, int index);
	FBowlingFrame(int first, int second, int third, int index);
};
