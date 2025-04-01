// Fill out your copyright notice in the Description page of Project Settings.


#include "BowlingFrame.h"

FBowlingFrame::FBowlingFrame() : FirstThrow(0), SecondThrow(0), ThirdThrow(0), FrameIndex(0), ScoreType(EScoreType::EST_None), ProcessedScore(0)
{
}

FBowlingFrame::~FBowlingFrame()
{
}

FBowlingFrame::FBowlingFrame(int first, int second,int index) :
	FrameIndex(index),
	FirstThrow(first),
	SecondThrow(second),
	FrameScore(first + second),
	ScoreType((FrameScore == 10) ? (first == 10 ? EScoreType::EST_Strike : EScoreType::EST_Spare) : EScoreType::EST_Normal)
{
}

FBowlingFrame::FBowlingFrame(int first, int second, int third, int index) :
	FrameIndex(index),
	FirstThrow(first),
	SecondThrow(second),
	ThirdThrow(third),
	FrameScore(first + second + third),
	ScoreType((FrameScore == 10) ? (first == 10 ? EScoreType::EST_Strike : EScoreType::EST_Spare) : EScoreType::EST_Normal)
{
}
