// Fill out your copyright notice in the Description page of Project Settings.


#include "../Managers/ChessGameModeBase.h"
#include "../Pieces/ChessPiece.h"
#include "../Pieces/Ch_KingPiece.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"


AChessGameModeBase::AChessGameModeBase()
{
}

void AChessGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    m_whiteDeadPieceLoc = FVector(50, -55, 0);
    m_blackDeadPieceLoc = FVector(300, 405, 0);
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

void AChessGameModeBase::SetTeamInCheck(EPieceTeam team, bool inCheck)
{
    switch (team)
    {
    case EPieceTeam::White:
        bWhiteKingChecked = inCheck;
        break;
    case EPieceTeam::Black:
        bBlackKingChecked = inCheck;
        break;
    }
}

bool AChessGameModeBase::GetTeamInCheck(EPieceTeam team)
{
    switch (team)
    {
    case EPieceTeam::White:
        return bWhiteKingChecked;
        break;
    case EPieceTeam::Black:
        return bBlackKingChecked;
        break;
    default:
        return false;
    }

    return false;
}

bool AChessGameModeBase::IsKingStillInCheck(EPieceTeam team, AChessBoardCell* potentialCell, EPieceType pieceType)
{
    TArray<AChessBoardCell*> moveableCells;
        //With Current Team asking if its in check (so see if Opposite team is checking)
        switch (team)
        {
        case EPieceTeam::White:
            moveableCells = GetTeamNextMove(EPieceTeam::Black);

            for (auto cells : moveableCells)
            {
                if (cells == whiteKingPiece->GetCurrentCell() && pieceType != EPieceType::King)
                {
                    return true;
                }
            }
            return false;
            break;

        case EPieceTeam::Black:
            moveableCells = GetTeamNextMove(EPieceTeam::White);
            for (auto cells : moveableCells)
            {
                if (cells == blackKingPiece->GetCurrentCell() && pieceType != EPieceType::King)
                {
                    return true;
                }
            }
            return false;
            break;
        default:
            return false;
        }
}

void AChessGameModeBase::RemovePieceFromTeam(EPieceTeam team, AChessPiece* piece)
{
    switch (team)
    {
    case EPieceTeam::White:
        AliveBlackTeam.Remove(piece);
        DeadBlackTeam.Add(piece);
        break;
    case EPieceTeam::Black:
        AliveWhiteTeam.Remove(piece);
        DeadWhiteTeam.Add(piece);
        break;
    }
}

TArray<AChessBoardCell*> AChessGameModeBase::GetTeamNextMove(EPieceTeam oppositeTeam)
{
    switch (oppositeTeam)
    {
    case EPieceTeam::White:
        t_whiteNextMove.Empty();
        for (auto aliveTeam : AliveWhiteTeam)
        {
            t_whiteNextMove += aliveTeam->CheckNextMove();
        }
        return t_whiteNextMove;
        break;
    case EPieceTeam::Black:
        t_blackNextMove.Empty();
        for (auto aliveTeam : AliveBlackTeam)
        {
            t_blackNextMove += aliveTeam->CheckNextMove();
        }
        return t_blackNextMove;
        break;
    }
    return TArray<AChessBoardCell*>();
}

void AChessGameModeBase::KingInCheck(EPieceTeam team)
{
    switch (team)
    {
    case EPieceTeam::White:
        bWhiteKingChecked = true;
        UE_LOG(LogTemp, Warning, TEXT("White King in Check"));
        break;
    case EPieceTeam::Black:
        bBlackKingChecked = true;
        UE_LOG(LogTemp, Warning, TEXT("Black King in Check"));
        break;
    }
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


