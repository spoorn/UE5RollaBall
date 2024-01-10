// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallGameModeBase.h"

#include "RollaBallWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RollaBall/Items/RollaBallItemBase.h"

void ARollaBallGameModeBase::ItemCollected()
{
	++ItemsCollected;
	UpdateItemText();
}

void ARollaBallGameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollaBallItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if (GameWidgetClass)
	{
		GameWidget = Cast<URollaBallWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ARollaBallGameModeBase::UpdateItemText()
{
	// Calls the blueprint function
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}
