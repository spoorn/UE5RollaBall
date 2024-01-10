// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollaBallGameModeBase.generated.h"

class URollaBallWidget;

/**
 * 
 */
UCLASS()
class ROLLABALL_API ARollaBallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ItemCollected();

protected:
	int32 ItemsCollected{0};
	int32 ItemsInLevel{0};

	// Widget variables

	// Allow us to define type of widget to display in editor
	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<UUserWidget> GameWidgetClass;

	UPROPERTY()
	URollaBallWidget* GameWidget;

	virtual void BeginPlay() override;

	void UpdateItemText();
	
};
