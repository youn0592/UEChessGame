// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/Ch_KingPiece.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"

ACh_KingPiece::ACh_KingPiece()
{
}

void ACh_KingPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACh_KingPiece::BeginPlay()
{
    Super::BeginPlay();
}

void ACh_KingPiece::CalculateMove()
{
    int loopIndex = m_KingMoves.Num();
    AChessBoardCell* NewCell;

    for (int i = 0; i < loopIndex; i++)
    {
        int newX = m_xIndex + m_KingMoves[i].X;
        int newY = m_yIndex + m_KingMoves[i].Y;

        if (m_gameBoard->GetCellAtIndex(newX, newY) && IsCellEmpty(newX, newY))
        {
            NewCell = m_gameBoard->GetCellAtIndex(newX, newY);
            NewCell->SetSelectedMaterial(1);
            m_moveableCells.Add(NewCell);
        }
    }

}

