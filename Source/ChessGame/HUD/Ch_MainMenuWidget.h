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

protected:
	virtual void NativeConstruct() override;

public:
protected:

	UPROPERTY(meta = (BindWidget))
		UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
		UButton* CreditButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;

private:

	AChessMenuGamemode* m_Gamemode;

};
