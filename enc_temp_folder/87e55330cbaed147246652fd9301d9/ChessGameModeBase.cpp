// Fill out your copyright notice in the Description page of Project Settings.


#include "../Managers/ChessGameModeBase.h"
#include "../Board/ChessBoard.h"


AChessGameModeBase::AChessGameModeBase()
{
}

void AChessGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    m_whiteDeadPieceLoc = FVector(50, -70, 0);
    m_blackDeadPieceLoc = FVector(300, 420, 0);
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

void AChessGameModeBase::SetDeadPieceLocation(EPieceTeam team, FVector nextLoc)
{
    switch (team)
    {
    case EPieceTeam::White:
        if (nextLoc.X >= 300)
        {
            nextLoc.Y -= 25;
            nextLoc.X = 50;
        }
        m_whiteDeadPieceLoc = nextLoc;
        break;
    case EPieceTeam::Black:
        if (nextLoc.X <= 50)
        {
            nextLoc.Y += 25;
            nextLoc.X = 300;
        }
        m_blackDeadPieceLoc = nextLoc;
        break;
    default:
        break;
    }
}

FVector AChessGameModeBase::GetDeadPieceLocation(EPieceTeam team)
{
    switch (team)
    {
    case EPieceTeam::White:
        return m_whiteDeadPieceLoc;
        break;
    case EPieceTeam::Black:
        return m_blackDeadPieceLoc;
        break;
    default:
        return m_whiteDeadPieceLoc;
        break;
    }
}

