// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/Ch_PawnPopupWidget.h"
#include "../Managers/ChessGameModeBase.h"
#include <Components/Button.h>

void UCh_PawnPopupWidget::NativeConstruct()
{
    Super::NativeConstruct();

    QueenButton->OnClicked.AddUniqueDynamic(this, &UCh_PawnPopupWidget::QueenPieceSelected);
    RookButton->OnClicked.AddUniqueDynamic(this, &UCh_PawnPopupWidget::RookPieceSelected);
    KnightButton->OnClicked.AddUniqueDynamic(this, &UCh_PawnPopupWidget::KnightPieceSelected);
    BishopButton->OnClicked.AddUniqueDynamic(this, &UCh_PawnPopupWidget::BishopPieceSelected);

    m_Gamemode = Cast<AChessGameModeBase>(GetWorld()->GetAuthGameMode());
    if (m_Gamemode == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode was null in PawnPopupWindow"));
    }
}

void UCh_PawnPopupWidget::QueenPieceSelected()
{
    if (m_Gamemode == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode was null in PawnPopupWindow"));
    }

    m_Gamemode->TransformPawn(EPieceType::Queen);
}

void UCh_PawnPopupWidget::RookPieceSelected()
{
    if (m_Gamemode == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode was null in PawnPopupWindow"));
    }

    m_Gamemode->TransformPawn(EPieceType::Rook);
}

void UCh_PawnPopupWidget::KnightPieceSelected()
{
    if (m_Gamemode == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode was null in PawnPopupWindow"));
    }

    m_Gamemode->TransformPawn(EPieceType::Knight);
}

void UCh_PawnPopupWidget::BishopPieceSelected()
{
    if (m_Gamemode == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode was null in PawnPopupWindow"));
    }

    m_Gamemode->TransformPawn(EPieceType::Bishop);
}
