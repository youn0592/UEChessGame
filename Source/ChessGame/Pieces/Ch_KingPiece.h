// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pieces/ChessPiece.h"
#include "Ch_KingPiece.generated.h"

/**
 *
 */

class AChessPieceCell;

UCLASS()
class CHESSGAME_API ACh_KingPiece : public AChessPiece
{
    GENERATED_BODY()

public:

    ACh_KingPiece();

    virtual void Tick(float DeltaTime) override;
    virtual void CheckSelectedCell(AChessBoardCell* selectedCell) override;
    virtual void PieceUnselected() override;
    TArray<AChessBoardCell*> CheckKingNextMove();

protected:

    virtual void BeginPlay() override;
    virtual void MovePiece(AChessBoardCell* selectedCell) override;
    virtual void CalculateMove(bool bDrawRender) override;

public:

    bool bInCheck = false;

protected:

    bool bFirstMove = true;

    TArray<FIntVector2> m_KingMoves{ {0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,-1},{-1, 1},{1,-1} };
    TArray<AChessBoardCell*> m_CastleCells;

private:
};
