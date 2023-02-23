// Fill out your copyright notice in the Description page of Project Settings.


#include "../Managers/ChessGameModeBase.h"
#include "../Pieces/ChessPiece.h"
#include "../Pieces/Ch_PawnPiece.h"
#include "../Pieces/Ch_KingPiece.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"
#include "../HUD/Ch_ChessHUD.h"


AChessGameModeBase::AChessGameModeBase()
{
}

void AChessGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    m_whiteDeadPieceLoc = FVector(50, -74, 0);
    m_blackDeadPieceLoc = FVector(300, 420, 0);
    m_CurrentTeam = EPieceTeam::White;

    m_ChessHUD = Cast<ACh_ChessHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
    if (m_ChessHUD == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Chess HUD was null in Gamemode"));
    }
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
    case EPieceTeam::Empty:
        m_CurrentTeam = EPieceTeam::Empty;
        break;
    default:
        break;
    }
    m_ChessHUD->SetCurrentTeam(m_CurrentTeam);
}

EPieceTeam AChessGameModeBase::GetCurrentTeam()
{
    return m_CurrentTeam;
}

void AChessGameModeBase::SetTeamInCheck(EPieceTeam enemyTeam, bool inCheck)
{
    switch (enemyTeam)
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
        if (bPotCheckMate == false)
        {
            m_ChessHUD->SetTeamInCheck(EPieceTeam::White, false);
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
        if (bPotCheckMate == false)
        {
            m_ChessHUD->SetTeamInCheck(EPieceTeam::Black, false);
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
        AliveWhiteTeam.Remove(piece);
        DeadWhiteTeam.Add(piece);
        break;
    case EPieceTeam::Black:
        AliveBlackTeam.Remove(piece);
        DeadBlackTeam.Add(piece);
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

void AChessGameModeBase::KingInCheck(EPieceTeam team, AChessPiece* checkingPiece)
{
    TArray<AChessBoardCell*> KingCells;
    CheckingPiece = checkingPiece;
    TArray<AChessBoardCell*> DeathCells;
    switch (team)
    {
    case EPieceTeam::White:
        bWhiteKingChecked = true;
        m_ChessHUD->SetTeamInCheck(EPieceTeam::White, bWhiteKingChecked);
        KingCells = whiteKingPiece->CheckKingNextMove();
        //DeathCells = GetTeamNextMove(EPieceTeam::Black);
        if (KingCells.Num() <= 0)
        {
            CheckForMate(EPieceTeam::White);
        }
        CheckingPiece = nullptr;
        break;
    case EPieceTeam::Black:
        bBlackKingChecked = true;
        m_ChessHUD->SetTeamInCheck(EPieceTeam::Black, bBlackKingChecked);
        KingCells = blackKingPiece->CheckKingNextMove();
        if (KingCells.Num() <= 0)
        {
            CheckForMate(EPieceTeam::Black);
        }
        CheckingPiece = nullptr;
        break;
    }
}

void AChessGameModeBase::CheckForMate(EPieceTeam team)
{
    if (m_CurrentTeam == team) { return; }
    TArray<AChessBoardCell*> moveableCells;
    TArray<AChessBoardCell*> killingCells;
    AChessPiece* empty = GetWorld()->SpawnActor<AChessPiece>();
    EPieceType checkingPieceType = CheckingPiece->GetPieceType();
    bool bKingNotMated = false;
    bPotCheckMate = true;

    moveableCells = GetTeamNextMove(team);
    killingCells = CheckingPiece->CheckNextMove();
    for (auto moveCells : moveableCells)
    {
        if (moveCells->GetChessPieceOnCell() == nullptr)
        {
            moveCells->SetChessPieceOnCell(empty);
        }
        if (!IsKingStillInCheck(team, moveCells, checkingPieceType))
        {
            bKingNotMated = true;
        }
        if (moveCells->GetChessPieceOnCell() == empty)
        {
            moveCells->SetChessPieceOnCell(nullptr);
        }
        if (bKingNotMated == true)
        {
            bPotCheckMate = false;
            return;
        }
    }
    m_ChessHUD->SetCheckMate(team);
    SetCurrentTeam(EPieceTeam::Empty);
    bPotCheckMate = false;

}

void AChessGameModeBase::PawnReachedEnd(ACh_PawnPiece* pawn)
{
    m_EndedPawn = pawn;
    m_CurrentTeam = EPieceTeam::Empty;
    m_ChessHUD->ShowPawnPopupWindow(true);
}

void AChessGameModeBase::TransformPawn(EPieceType pieceType)
{
    AChessBoardCell* newCell;
    newCell = m_EndedPawn->GetCurrentCell();
    FVector hellLoc;
    FVector pawnLoc = m_EndedPawn->GetActorLocation();
    EPieceTeam pawnTeam = m_EndedPawn->GetTeam();
    AChessPiece* tempPiece;
    for (auto pieces : ExtraPieces)
    {
        if (pieces->GetPieceType() == pieceType)
        {
            hellLoc = pieces->GetActorLocation();
            tempPiece = pieces;
            tempPiece->SetTeam(pawnTeam);
            tempPiece->SetActorLocation(pawnLoc);
            tempPiece->SetCurrentCell(newCell);
            newCell->SetChessPieceOnCell(tempPiece);
            break;
        }
    }
    m_EndedPawn->SetActorLocation(hellLoc);
    switch (pawnTeam)
    {
    case EPieceTeam::White:
        AliveWhiteTeam.Add(tempPiece);
        AliveWhiteTeam.Remove(m_EndedPawn);
        break;
    case EPieceTeam::Black:
        AliveBlackTeam.Add(tempPiece);
        AliveBlackTeam.Remove(m_EndedPawn);
        break;
    }
    m_ChessHUD->ShowPawnPopupWindow(false);
    m_EndedPawn->SetCurrentCell(nullptr);
    m_CurrentTeam = m_EndedPawn->GetOppositeTeam();
    m_EndedPawn = nullptr;
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


