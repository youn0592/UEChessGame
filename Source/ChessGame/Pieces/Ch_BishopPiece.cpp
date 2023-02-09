// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/Ch_BishopPiece.h"
#include "../Board/ChessBoard.h"
#include "../Managers/ChessGameModeBase.h"
#include "../Board/ChessBoardCell.h"

ACh_BishopPiece::ACh_BishopPiece()
{
    m_PieceType = EPieceType::Bishop;
}

void ACh_BishopPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

TArray<AChessBoardCell*> ACh_BishopPiece::CheckNextMove()
{
    m_moveableCells.Empty();
    CalculateMove(false);
    return m_moveableCells;
}

void ACh_BishopPiece::BeginPlay()
{
    Super::BeginPlay();
}

void ACh_BishopPiece::CalculateMove(bool bDrawRender)
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
