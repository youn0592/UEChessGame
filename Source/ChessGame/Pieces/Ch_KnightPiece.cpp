// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/Ch_KnightPiece.h"
#include "../Managers/ChessGameModeBase.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"

ACh_KnightPiece::ACh_KnightPiece()
{
    m_PieceType = EPieceType::Knight;
}

void ACh_KnightPiece::BeginPlay()
{
    Super::BeginPlay();
}

void ACh_KnightPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

TArray<AChessBoardCell*> ACh_KnightPiece::CheckNextMove()
{
    m_moveableCells.Empty();
    CalculateMove(false);
    return m_moveableCells;
}

void ACh_KnightPiece::CalculateMove(bool bDrawRender)
{
    if (!bIsAlive) { return; }
    int loopIndex = m_KnightMoves.Num();
    AChessBoardCell* NewCell;

    for (int i = 0; i < loopIndex; i++)
    {
        int newX = m_xIndex + m_KnightMoves[i].X;
        int newY = m_yIndex + m_KnightMoves[i].Y;

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
                if (bDrawRender == false && NewCell->IsKingOnCell() && m_Gamemode->CheckingPiece != this)
                {
                    m_Gamemode->KingInCheck(m_OppositeTeam, this);
                    m_moveableCells.Add(NewCell);
                }

                NewCell->SetSelectedMaterial(2, bDrawRender);
                m_moveableCells.Add(NewCell);
            }
        }

    }
}


