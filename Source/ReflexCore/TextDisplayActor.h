// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TextDisplayActor.generated.h"

UENUM(BlueprintType)
enum class ETextDisplayCategory : uint8
{
	none,
	score,
	timer,
	accuracyRate,
	difficulty,
	startMode,
	endMode,
	restartMode,
};

UCLASS()
class REFLEXCORE_API ATextDisplayActor : public AActor
{
	GENERATED_BODY()
	
public :	
	ATextDisplayActor();

	void UpdateDisplayValue(float value);
	void UpdateDisplayValue();

	ETextDisplayCategory GetDisplayCategory() { return displayCategory; }

protected :
	virtual void BeginPlay() override;

private :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text", meta = (AllowPrivateAccess = "true"))
	ETextDisplayCategory displayCategory = ETextDisplayCategory::none;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text", meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* textRender;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* collisionComp;
};
