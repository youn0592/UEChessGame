// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pieces/ChessPiece.h"
#include "Ch_RookPiece.generated.h"

/**
 * 
 */
UCLASS()
class CHESSGAME_API ACh_RookPiece : public AChessPiece
{
	GENERATED_BODY()

public:

	ACh_RookPiece();

	virtual void Tick(float DeltaTime) override;
	virtual TArray<AChessBoardCell*> CheckNextMove() override;
	virtual void CheckSelectedCell(AChessBoardCell* selectedCell) override;

	void SetCanCastle(bool bCastle) { bCastling = bCastle; }
	bool CanCastleRook();

protected:

	virtual void BeginPlay() override;

	virtual void MovePiece(AChessBoardCell* selectedCell) override;
	virtual void CalculateMove(bool bDrawRender) override;

public:

protected:

	bool bFirstMove = true;

private:
	

};
