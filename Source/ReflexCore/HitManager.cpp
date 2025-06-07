// Fill out your copyright notice in the Description page of Project Settings.


#include "HitManager.h"
#include "TextDisplayActor.h"

void UHitManager::Init(ATextDisplayActor *inScoreActor, ATextDisplayActor *inAccuracyActor)
{
    scoreDisplayActor = inScoreActor;
    accuracyDisplayActor = inAccuracyActor;
}

void UHitManager::ProcessHit(bool bDidHit)
{
    totalShots++;

    if(bDidHit)
    {
        hitCount++;
        score++;
    }
    
    UpdateTextDisplays();
}

void UHitManager::ResetStats()
{
    totalShots = 0;
    hitCount = 0;
    score = 0;

    UpdateTextDisplays();
}

void UHitManager::HitTextDisplay()
{
    totalShots--;
}

float UHitManager::GetAccuracyRate() const
{
    return (totalShots > 0) ? (static_cast<float>(hitCount) / totalShots) * 100.f : 0.f;
}

void UHitManager::UpdateTextDisplays()
{
    if(scoreDisplayActor)
    {
        scoreDisplayActor->UpdateDisplayValue(score);
    }

    if(accuracyDisplayActor)
    {
        accuracyDisplayActor->UpdateDisplayValue(GetAccuracyRate());
    }
}
