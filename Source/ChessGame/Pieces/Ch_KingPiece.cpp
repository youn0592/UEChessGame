// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/Ch_KingPiece.h"
#include "../Pieces/Ch_RookPiece.h"
#include "../Managers/ChessGameModeBase.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"

ACh_KingPiece::ACh_KingPiece()
{
    m_PieceType = EPieceType::King;
}

void ACh_KingPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACh_KingPiece::CheckSelectedCell(AChessBoardCell* selectedCell)
{
    for (int i = 0; i < m_CastleCells.Num(); i++)
    {
        if (m_CastleCells[i] == selectedCell)
        {
            ACh_RookPiece* m_Rook = Cast<ACh_RookPiece>(selectedCell->GetChessPieceOnCell());
            int SCX, SCY, KNI, RNI, KNY, RNY;
            KNI = -2; RNI = 2;
            selectedCell->GetIndex(SCX, SCY);
            if (SCY == 7)
            {
                KNI *= -1; RNI = -3;
            }
            KNY = m_yIndex + KNI;
            RNY = SCY + RNI;
            selectedCell = m_gameBoard->GetCellAtIndex(m_xIndex, KNY);
            m_moveableCells.Add(m_gameBoard->GetCellAtIndex(m_xIndex, KNY));
            AChessBoardCell* rookCell = m_gameBoard->GetCellAtIndex(m_xIndex, RNY);
            m_CastleCells[i]->SetSelectedMaterial(0, true);
            m_Rook->SetCanCastle(true);
            m_Rook->CheckSelectedCell(rookCell);
            m_CastleCells.Empty();
            break;
        }
        m_CastleCells[i]->SetSelectedMaterial(0, true);
    }

    Super::CheckSelectedCell(selectedCell);
}

void ACh_KingPiece::PieceUnselected()
{
    m_CastleCells.Empty();
    Super::PieceUnselected();
}

//TArray<AChessBoardCell*> ACh_KingPiece::CheckNextMove()
//{
//    m_moveableCells.Empty();
//    CalculateMove(false);
//    return m_moveableCells;
//}

void ACh_KingPiece::BeginPlay()
{
    Super::BeginPlay();
}

void ACh_KingPiece::MovePiece(AChessBoardCell* selectedCell)
{
    if (bFirstMove) { bFirstMove = false; }
    Super::MovePiece(selectedCell);
}

void ACh_KingPiece::CalculateMove(bool bDrawRender)
{
    if (!bIsAlive) { return; }
    int loopIndex = m_KingMoves.Num();
    bool bSkipRun = false;
    TArray<AChessBoardCell*> potentialDeathCells = m_Gamemode->GetTeamNextMove(m_OppositeTeam);
    AChessBoardCell* NewCell;

    for (int i = 0; i < loopIndex; i++)
    {
        int newX = m_xIndex + m_KingMoves[i].X;
        int newY = m_yIndex + m_KingMoves[i].Y;

        for (auto deathCell : potentialDeathCells)
        {
            if (m_gameBoard->GetCellAtIndex(newX, newY) == deathCell)
            {
                bSkipRun = true;
                break;
            }
        }

        if (bSkipRun == true)
        {
            bSkipRun = false;
            continue;
        }

        if (m_gameBoard->GetCellAtIndex(newX, newY) && IsCellEmpty(newX, newY))
        {
            NewCell = m_gameBoard->GetCellAtIndex(newX, newY);
            NewCell->SetSelectedMaterial(1, bDrawRender);
            m_moveableCells.Add(NewCell);
        }
        else if (m_gameBoard->GetCellAtIndex(newX, newY) && !IsCellEmpty(newX, newY))
        {
            NewCell = m_gameBoard->GetCellAtIndex(newX, newY);
            if (NewCell->GetChessPieceOnCell()->GetTeam() == m_OppositeTeam)
            {
                NewCell->SetSelectedMaterial(2, bDrawRender);
                m_moveableCells.Add(NewCell);
            }
        }

    }
    if (!bDrawRender) { return; }
    NewCell = nullptr;

    if (bFirstMove && (!IsCellEmpty(m_xIndex, 0) || !IsCellEmpty(m_xIndex, 7)))
    {
        int index = 0;
        for (int i = 0; i < 2; i++)
        {
            NewCell = m_gameBoard->GetCellAtIndex(m_xIndex, index);
            if (NewCell->GetChessPieceOnCell()->GetTeam() == m_CurrentTeam)
            {
                ACh_RookPiece* CastleRook = Cast<ACh_RookPiece>(NewCell->GetChessPieceOnCell());
                if (CastleRook->CanCastleRook())
                {
                    NewCell->SetSelectedMaterial(3, bDrawRender);
                    m_CastleCells.Add(NewCell);
                    break;
                }
                index = 7;
                continue;
            }
        }
    }

}

