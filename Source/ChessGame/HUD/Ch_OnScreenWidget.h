// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Ch_OnScreenWidget.generated.h"

/**
 * 
 */

class UTextBlock;
class UCh_PawnPopupWidget;
class UVerticalBox;
class UCanvasPanel;
class USlateBrushAsset;
class UButton;
class UImage;

UCLASS()
class CHESSGAME_API UCh_OnScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetPopupWindow(bool bActive);
	void SetCurrentTeam(FString name);
	void SetTeamInCheck(FString name, bool bActive);
	void SetCheckmatePanel(FString name);

protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void ResetLevel();

	UFUNCTION()
		void ReturnToMenu();
	UFUNCTION()
		void QuitGame();

public:

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI Images")
		TArray<USlateBrushAsset*> UiImages;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TurnMoveBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TeamInCheck;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CheckmateTeam;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* CheckTextVBox;	
	
	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* CheckmatePanel;

	UPROPERTY(meta = (BindWidget))
		UButton* ReloadSceneButton;

	UPROPERTY(meta = (BindWidget))
		UButton* ReturnToMenuButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
		UCh_PawnPopupWidget* PawnPopupWindow;

	UPROPERTY(meta = (BindWidget))
		UImage* IconImage;

	bool bIsWhiteTeam;
	
};
