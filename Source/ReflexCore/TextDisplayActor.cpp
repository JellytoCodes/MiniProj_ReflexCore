// Fill out your copyright notice in the Description page of Project Settings.


#include "TextDisplayActor.h"
#include "Components/TextRenderComponent.h"

ATextDisplayActor::ATextDisplayActor()
{
	PrimaryActorTick.bCanEverTick = false;

	textRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	RootComponent = textRender;

	textRender->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	textRender->SetTextRenderColor(FColor::Cyan);
	textRender->SetWorldSize(80.f);
}

void ATextDisplayActor::BeginPlay()
{
	Super::BeginPlay();
	
	if(displayCategory == ETextDisplayCategory::score) UpdateDisplayValue(0);
	else if(displayCategory == ETextDisplayCategory::timer) UpdateDisplayValue(0);
	else if(displayCategory == ETextDisplayCategory::accuracyRate) UpdateDisplayValue(100.f);
}

void ATextDisplayActor::UpdateDisplayValue(float value)
{
	switch(displayCategory)
	{
		case ETextDisplayCategory::score :
			textRender->SetText(FText::FromString(FString::Printf(TEXT("Score : %.0f"), value)));
		break;

		case ETextDisplayCategory::timer :
			textRender->SetText(FText::FromString(FString::Printf(TEXT("Time : %.0f"), value)));
		break;

		case ETextDisplayCategory::accuracyRate :
			textRender->SetText(FText::FromString(FString::Printf(TEXT("accuracy Rate : %.2f"), value)));
		break;
	}
}
