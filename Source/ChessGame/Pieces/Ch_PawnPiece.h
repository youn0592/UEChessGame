// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "Ch_PawnPiece.generated.h"

/**
 *
 */
class AChessBoard;

UCLASS()
class CHESSGAME_API ACh_PawnPiece : public AChessPiece
{
    GENERATED_BODY()

public:

    ACh_PawnPiece();

    virtual void Tick(float DeltaTime) override;
    virtual void SetTeam(EPieceTeam team) override;

    virtual TArray<AChessBoardCell*> CheckNextMove() override;

protected:

    virtual void BeginPlay() override;

    virtual void CalculateMove(bool bDrawRender) override;
    void CalculateKill(bool bDrawRender);
    virtual void MovePiece(AChessBoardCell* selectedCell);


public:

protected:

    bool bFirstMove;
    int m_Direction;
    int m_EndGame;

private:


};
