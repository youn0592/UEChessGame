// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/Ch_QueenPiece.h"
#include "../Managers/ChessGameModeBase.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"

ACh_QueenPiece::ACh_QueenPiece()
{
    m_PieceType = EPieceType::Queen;
}

void ACh_QueenPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

TArray<AChessBoardCell*> ACh_QueenPiece::CheckNextMove()
{
    m_moveableCells.Empty();
    CalculateMove(false);
    return m_moveableCells;
}

void ACh_QueenPiece::BeginPlay()
{
    Super::BeginPlay();
}

void ACh_QueenPiece::CalculateMove(bool bDrawRender)
{
    if (!bIsAlive) { return; }
    int nextIndex = 1;
    int nextAltIndex = 0;
    int loopIndex = m_boardSizeX * 2;

    int newX, newY;
    newX = m_xIndex;
    newY = m_yIndex;

    bool bIsPositive = true;
    bool bIsAltPostive = true;
    AChessBoardCell* NewCell;

    for (int i = 0; i < loopIndex; i++)
    {
        newX += nextIndex;
        newY += nextAltIndex;

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
                    if (m_Gamemode->GetTeamInCheck(m_OppositeTeam) == false)
                    {
                        m_Gamemode->KingInCheck(m_OppositeTeam, this);
                    }
                    m_moveableCells.Add(NewCell);
                    continue;
                }
                NewCell->SetSelectedMaterial(2, bDrawRender);
                m_moveableCells.Add(NewCell);
            }
        }

        if (bIsPositive)
        {
            newX = m_xIndex;
            nextIndex = -1;
            bIsPositive = false;
            continue;
        }
        if (bIsAltPostive)
        {
            newX = m_xIndex;
            newY = m_yIndex;
            nextIndex = 0;
            nextAltIndex = 1;
            bIsAltPostive = false;
            continue;
        }
        if (!bIsAltPostive)
        {
            newY = m_yIndex;
            nextAltIndex = -1;
            continue;
        }
        break;
    }

    newX = m_xIndex;
    newY = m_yIndex;
    nextIndex = 1;
    nextAltIndex = -1;
    bIsPositive = true;
    bIsAltPostive = true;

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
                    if (m_Gamemode->GetTeamInCheck(m_OppositeTeam) == false)
                    {
                        m_Gamemode->KingInCheck(m_OppositeTeam, this);
                    }
                    m_moveableCells.Add(NewCell);
                    continue;
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

