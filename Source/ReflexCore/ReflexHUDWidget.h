// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReflexHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class REFLEXCORE_API UReflexHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
private :
	UPROPERTY(meta = (BindWidget))
	class UImage* crossHair;
};
