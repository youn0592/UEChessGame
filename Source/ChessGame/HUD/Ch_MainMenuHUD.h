// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Ch_MainMenuHUD.generated.h"

/**
 * 
 */
class UUserWidget;
class UCh_MainMenuWidget;

UCLASS()
class CHESSGAME_API ACh_MainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

	ACh_MainMenuHUD();

	virtual void Tick(float DeltaTime) override;
	virtual void DrawHUD() override;

protected:

	virtual void BeginPlay() override;

public:
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<UUserWidget> BP_MainMenuWidget;

	UCh_MainMenuWidget* m_MainMenuWidget;

private:
	
};
