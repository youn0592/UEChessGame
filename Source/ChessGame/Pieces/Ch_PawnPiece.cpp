// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/Ch_PawnPiece.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"

ACh_PawnPiece::ACh_PawnPiece()
{
}

void ACh_PawnPiece::BeginPlay()
{
    Super::BeginPlay();

    bFirstMove = true;
}

void ACh_PawnPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACh_PawnPiece::SetTeam(EPieceTeam team)
{
    Super::SetTeam(team);

    switch (team)
    {
    case EPieceTeam::White:
        m_Direction = 1;
        break;
        
    case EPieceTeam::Black:
        m_Direction = -1;
        break;
    }
}

void ACh_PawnPiece::MovePiece(AChessBoardCell* selectedCell)
{
    Super::MovePiece(selectedCell);
    if (bFirstMove) { bFirstMove = false; }
}

void ACh_PawnPiece::CalculateMove()
{
    int loopIndex;
    loopIndex = 1 + bFirstMove;
    int newX = m_xIndex;
    AChessBoardCell* NewCell;

    for (int i = 0; i < loopIndex; i++)
    {
        newX += m_Direction;

        if (m_gameBoard->GetCellAtIndex(newX, m_yIndex) && IsCellEmpty(newX, m_yIndex))
        {
            NewCell = m_gameBoard->GetCellAtIndex(newX, m_yIndex);
            NewCell->SetSelectedMaterial(1);
            m_moveableCells.Add(NewCell);
            continue;
        }
        break;
    }
}


