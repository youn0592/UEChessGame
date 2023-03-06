// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Ch_MainMenuWidget.generated.h"

/**
 * 
 */
class UButton;
class AChessMenuGamemode;

UCLASS()
class CHESSGAME_API UCh_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void PlayGame();
	UFUNCTION()
	void CreditSelected();
	UFUNCTION()
	void QuitGame();

	UFUNCTION()
		void BackSelected();

protected:
	virtual void NativeConstruct() override;

public:
protected:

	UPROPERTY(meta = (BindWidget))
		UPanelWidget* MainMenuPanel;

	UPROPERTY(meta = (BindWidget))
		UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
		UButton* CreditButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
		UPanelWidget* CreditsPanel;

	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;


private:

	AChessMenuGamemode* m_Gamemode;

};
