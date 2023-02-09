// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../ChessGame.h"
#include "Ch_PawnPopupWidget.generated.h"

/**
 *
 */

class UButton;
class AChessGameModeBase;

UCLASS()
class CHESSGAME_API UCh_PawnPopupWidget : public UUserWidget
{
    GENERATED_BODY()
public:
protected:

    virtual void NativeConstruct() override;

    UFUNCTION()
        void QueenPieceSelected();

    UFUNCTION()
        void RookPieceSelected();

    UFUNCTION()
        void KnightPieceSelected();

    UFUNCTION()
        void BishopPieceSelected();
public:
protected:

    AChessGameModeBase* m_Gamemode;

    UPROPERTY(meta = (BindWidget))
        UButton* QueenButton;

    UPROPERTY(meta = (BindWidget))
        UButton* RookButton;

    UPROPERTY(meta = (BindWidget))
        UButton* KnightButton;

    UPROPERTY(meta = (BindWidget))
        UButton* BishopButton;
};
