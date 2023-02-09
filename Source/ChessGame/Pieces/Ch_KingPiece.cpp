// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/Ch_KingPiece.h"
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

void ACh_KingPiece::AddCheckingPiece(AChessPiece* checkingPiece)
{
    m_CheckedPieces.Add(checkingPiece);
}

TArray<AChessPiece*> ACh_KingPiece::GetCheckingPieces()
{
    return m_CheckedPieces;
}

void ACh_KingPiece::BeginPlay()
{
    Super::BeginPlay();
}

void ACh_KingPiece::CalculateMove(bool bDrawRender)
{
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

}

