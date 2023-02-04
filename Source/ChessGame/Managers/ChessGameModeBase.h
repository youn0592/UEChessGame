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
class ACh_KingPiece;

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
    void KingInCheck(EPieceTeam team);

protected:

    virtual void BeginPlay() override;

public:

    ACh_KingPiece* whiteKingPiece;
    ACh_KingPiece* blackKingPiece;

    TArray<AChessPiece*> AliveWhiteTeam;
    TArray<AChessPiece*> DeadWhiteTeam;

    TArray<AChessPiece*> AliveBlackTeam;
    TArray<AChessPiece*> DeadBlackTeam;

protected:

    bool bWhiteKingChecked = false, bBlackKingChecked = false;
    TArray<AChessBoardCell*> t_whiteNextMove;
    TArray<AChessBoardCell*> t_blackNextMove;

    AChessBoard* m_ChessBoard;
    EPieceTeam m_CurrentTeam;

    FVector m_blackDeadPieceLoc, m_whiteDeadPieceLoc;

private:


};
