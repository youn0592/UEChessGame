// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/Ch_RookPiece.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"

ACh_RookPiece::ACh_RookPiece()
{
}

void ACh_RookPiece::BeginPlay()
{
    Super::BeginPlay();
}

void ACh_RookPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void ACh_RookPiece::CalculateMove()
{
    int nextIndex = 1;
    int nextAltIndex = 0;
    int loopIndex = m_boardSizeX * 2;

    int newX, newY;
    newX = m_xIndex;
    newY = m_yIndex;
    bool bIsPositve = true;
    bool bIsAltPositive = true;
    AChessBoardCell* NewCell;

    for (int i = 0; i < loopIndex; i++)
    {
        newX += nextIndex;
        newY += nextAltIndex;

        if (m_gameBoard->GetCellAtIndex(newX, newY) && IsCellEmpty(newX, newY))
        {
            NewCell = m_gameBoard->GetCellAtIndex(newX, newY);
            NewCell->SetSelectedMaterial(1);
            m_moveableCells.Add(NewCell);
            continue;
        }
        if (bIsPositve)
        {
            newX = m_xIndex;
            nextIndex = -1;
            bIsPositve = false;
            continue;
        }
        if (bIsAltPositive)
        {
            newX = m_xIndex;
            newY = m_yIndex;
            nextIndex = 0;
            nextAltIndex = 1;
            bIsAltPositive = false;
            continue;
        }
        if (!bIsAltPositive)
        {
            newY = m_yIndex;
            nextAltIndex = -1;
            continue;
        }
        break;
    }
}

