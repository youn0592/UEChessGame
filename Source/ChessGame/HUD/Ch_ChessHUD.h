// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../ChessGame.h"
#include "Ch_ChessHUD.generated.h"

/**
 * 
 */

class UUserWidget;
class UCh_OnScreenWidget;

UCLASS()
class CHESSGAME_API ACh_ChessHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	ACh_ChessHUD();

	virtual void Tick(float DeltaTime) override;
	virtual void DrawHUD() override;

	void ShowPawnPopupWindow(bool bActive);
	void SetCurrentTeam(EPieceTeam currentTeam);
	void SetTeamInCheck(EPieceTeam currentTeam, bool bActive);
	void SetCheckMate(EPieceTeam losingTeam);

protected:

	virtual void BeginPlay() override;

public:

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<UUserWidget> BP_OnScreenWidget;

	UCh_OnScreenWidget* m_OnScreenWidget;

private:
};
