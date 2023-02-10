// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/Ch_RookPiece.h"
#include "../Managers/ChessGameModeBase.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"

ACh_RookPiece::ACh_RookPiece()
{
    m_PieceType = EPieceType::Rook;
}

void ACh_RookPiece::BeginPlay()
{
    Super::BeginPlay();
}

void ACh_RookPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

TArray<AChessBoardCell*> ACh_RookPiece::CheckNextMove()
{
    m_moveableCells.Empty();
    CalculateMove(false);
    return m_moveableCells;
}

void ACh_RookPiece::CalculateMove(bool bDrawRender)
{
    int nextXIndex = 1;
    int nextYIndex = 0;
    int loopIndex = m_boardSizeX * 2;

    int newX, newY;
    newX = m_xIndex;
    newY = m_yIndex;
    bool bIsPositve = true;
    bool bIsAltPositive = true;
    AChessBoardCell* NewCell;

    for (int i = 0; i < loopIndex; i++)
    {
        newX += nextXIndex;
        newY += nextYIndex;

        if (m_gameBoard->GetCellAtIndex(newX, newY) && IsCellEmpty(newX, newY))
        {
            NewCell = m_gameBoard->GetCellAtIndex(newX, newY);
            NewCell->SetSelectedMaterial(1, bDrawRender);
            m_moveableCells.Add(NewCell);
            continue;
        }
        else if (m_gameBoard->GetCellAtIndex(newX, newY) && !IsCellEmpty(newX, newY))
        {
            NewCell = m_gameBoard->GetCellAtIndex(newX, newY);
            if (NewCell->GetChessPieceOnCell()->GetTeam() == m_OppositeTeam)
            {
                if (bDrawRender == false && NewCell->IsKingOnCell())
                {
                    
                    m_Gamemode->KingInCheck(m_OppositeTeam);
                }
                NewCell->SetSelectedMaterial(2, bDrawRender);
                m_moveableCells.Add(NewCell);
            }
        }

        if (bIsPositve)
        {
            newX = m_xIndex;
            nextXIndex = -1;
            bIsPositve = false;
            continue;
        }
        if (bIsAltPositive)
        {
            newX = m_xIndex;
            newY = m_yIndex;
            nextXIndex = 0;
            nextYIndex = 1;
            bIsAltPositive = false;
            continue;
        }
        if (!bIsAltPositive)
        {
            newY = m_yIndex;
            nextYIndex = -1;
            continue;
        }
        break;
    }
}


