// Fill out your copyright notice in the Description page of Project Settings.


#include "TextDisplayActor.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"

ATextDisplayActor::ATextDisplayActor()
{
	PrimaryActorTick.bCanEverTick = false;

	collisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = collisionComp;
	collisionComp->SetBoxExtent(FVector(100.f, 10.f, 30.f));
	collisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	collisionComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	textRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	textRender->SetupAttachment(collisionComp);

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
	else if(displayCategory == ETextDisplayCategory::startMode) UpdateDisplayValue();
	else if(displayCategory == ETextDisplayCategory::endMode) UpdateDisplayValue();
	else if(displayCategory == ETextDisplayCategory::restartMode) UpdateDisplayValue();
	else return;
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

void ATextDisplayActor::UpdateDisplayValue()
{
	switch(displayCategory)
	{
		case ETextDisplayCategory::startMode :
			textRender->SetText(FText::FromString(FString::Printf(TEXT("Start"))));
		break;

		case ETextDisplayCategory::endMode :
			textRender->SetText(FText::FromString(FString::Printf(TEXT("End"))));
		break;

		case ETextDisplayCategory::restartMode :
			textRender->SetText(FText::FromString(FString::Printf(TEXT("Restart"))));
		break;
	}
}
