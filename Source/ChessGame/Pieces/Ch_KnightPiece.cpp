// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/Ch_KnightPiece.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"

ACh_KnightPiece::ACh_KnightPiece()
{
}

void ACh_KnightPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACh_KnightPiece::BeginPlay()
{
    Super::BeginPlay();
}

void ACh_KnightPiece::CalculateMove()
{
    int loopIndex = m_KnightMoves.Num();
    AChessBoardCell* NewCell;

    for (int i = 0; i < loopIndex; i++)
    {
        int newX = m_xIndex + m_KnightMoves[i].X;
        int newY = m_yIndex + m_KnightMoves[i].Y;

        if (m_gameBoard->GetCellAtIndex(newX, newY) && IsCellEmpty(newX, newY))
        {
            NewCell = m_gameBoard->GetCellAtIndex(newX, newY);
            NewCell->SetSelectedMaterial(1);
            m_moveableCells.Add(NewCell);
        }
        else if (m_gameBoard->GetCellAtIndex(newX, newY) && !IsCellEmpty(newX, newY))
        {
            NewCell = m_gameBoard->GetCellAtIndex(newX, newY);
            if (NewCell->GetChessPieceOnCell()->GetTeam() == m_OppositeTeam)
            {
                NewCell->SetSelectedMaterial(2);
                m_moveableCells.Add(NewCell);
            }
        }

    }
}


