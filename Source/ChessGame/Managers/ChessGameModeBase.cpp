// Fill out your copyright notice in the Description page of Project Settings.


#include "../Managers/ChessGameModeBase.h"
#include "../Board/ChessBoard.h"


AChessGameModeBase::AChessGameModeBase()
{
}

void AChessGameModeBase::BeginPlay()
{    
    Super::BeginPlay();

    m_CurrentTeam = EPieceTeam::White;

}

void AChessGameModeBase::SetChessBoard(AChessBoard* newBoard)
{
    m_ChessBoard = newBoard;
}

AChessBoard* AChessGameModeBase::GetChessBoard()
{
    return m_ChessBoard;
}

void AChessGameModeBase::SetCurrentTeam(EPieceTeam team)
{
    switch (team)
    {
    case EPieceTeam::White:
        m_CurrentTeam = EPieceTeam::Black;
        break;

    case EPieceTeam::Black:
        m_CurrentTeam = EPieceTeam::White;
        break;
    default:
        break;
    }
}

EPieceTeam AChessGameModeBase::GetCurrentTeam()
{
    return m_CurrentTeam;
}

