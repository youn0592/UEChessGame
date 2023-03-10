// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ChessGame.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameModeBase.generated.h"

/**
 *
 */

class AChessBoard;
class AChessPiece;
class AChessBoardCell;
class ACh_PawnPiece;
class ACh_KingPiece;
class ACh_ChessHUD;

UCLASS()
class CHESSGAME_API AChessGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:

    AChessGameModeBase();

    void SetChessBoard(AChessBoard* newBoard);
    AChessBoard* GetChessBoard();
    void SetCurrentTeam(EPieceTeam team);
    EPieceTeam GetCurrentTeam();
    void SetTeamInCheck(EPieceTeam team, bool inCheck);
    bool GetTeamInCheck(EPieceTeam team);

    bool IsKingStillInCheck(EPieceTeam team, AChessBoardCell* potentialCell, EPieceType pieceType);

    void SetDeadPieceLocation(EPieceTeam team, FVector nextLoc);
    FVector GetDeadPieceLocation(EPieceTeam team);
    void RemovePieceFromTeam(EPieceTeam team, AChessPiece* piece);

    TArray<AChessBoardCell*> GetTeamNextMove(EPieceTeam oppositeTeam);
    void KingInCheck(EPieceTeam team, AChessPiece* checkingPiece);
    void CheckForMate(EPieceTeam team);

    void PawnReachedEnd(ACh_PawnPiece* pawn);
    void TransformPawn(EPieceType pieceType);

    bool IsKingCheckMated() { return bPotCheckMate; }

    void ResetGame();
    void QuitGame();
    void ReturnToMainMenu();

protected:

    virtual void BeginPlay() override;

public:


    ACh_KingPiece* whiteKingPiece;
    ACh_KingPiece* blackKingPiece;
    AChessPiece* CheckingPiece;

    TArray<AChessPiece*> AliveWhiteTeam;
    TArray<AChessPiece*> DeadWhiteTeam;

    TArray<AChessPiece*> AliveBlackTeam;
    TArray<AChessPiece*> DeadBlackTeam;

    TArray<AChessPiece*> ExtraPieces;

protected:

    bool bWhiteKingChecked = false, bBlackKingChecked = false, bPotCheckMate = false;
    TArray<AChessBoardCell*> t_whiteNextMove;
    TArray<AChessBoardCell*> t_blackNextMove;

    ACh_PawnPiece* m_EndedPawn;

    AChessBoard* m_ChessBoard;
    EPieceTeam m_CurrentTeam;

    ACh_ChessHUD* m_ChessHUD;

    FVector m_blackDeadPieceLoc, m_whiteDeadPieceLoc;

private:


};
