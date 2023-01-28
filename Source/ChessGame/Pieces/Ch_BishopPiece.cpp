// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/Ch_BishopPiece.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"

ACh_BishopPiece::ACh_BishopPiece()
{
}

void ACh_BishopPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACh_BishopPiece::BeginPlay()
{
    Super::BeginPlay();
}

void ACh_BishopPiece::CalculateMove()
{
    int newX, newY;
    newX = m_xIndex;
    newY = m_yIndex;
    int nextIndex = 1;
    int nextAltIndex = -1;
    int loopIndex = m_boardSizeX * 2;

    bool bIsPositive = true;
    bool bIsAltPostive = true;
    AChessBoardCell* NewCell;

    for (int i = 0; i < loopIndex; i++)
    {
        newX += nextIndex;
        newY -= nextAltIndex;
        if (m_gameBoard->GetCellAtIndex(newX, newY) && IsCellEmpty(newX, newY))
        {
            NewCell = m_gameBoard->GetCellAtIndex(newX, newY);
            NewCell->SetSelectedMaterial(1);
            m_moveableCells.Add(NewCell);
            continue;
        }
        if (bIsPositive)
        {
            newX = m_xIndex;
            newY = m_yIndex;
            nextIndex *= -1;
            nextAltIndex *= -1;
            bIsPositive = false;
            continue;
        }
        if (bIsAltPostive)
        {
            newX = m_xIndex;
            newY = m_yIndex;
            nextAltIndex *= -1;
            bIsAltPostive = false;
            continue;
        }
        if (!bIsAltPostive)
        {
            newX = m_xIndex;
            newY = m_yIndex;
            nextIndex *= -1;
            nextAltIndex *= -1;
            continue;
        }
        break;
    }

}
