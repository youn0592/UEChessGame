// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pieces/ChessPiece.h"
#include "Ch_KingPiece.generated.h"

/**
 * 
 */
UCLASS()
class CHESSGAME_API ACh_KingPiece : public AChessPiece
{
	GENERATED_BODY()
	
public:

	ACh_KingPiece();

	virtual void Tick(float DeltaTime) override;

	void AddCheckingPiece(AChessPiece* checkingPiece);
	TArray<AChessPiece*> GetCheckingPieces();

protected:

	virtual void BeginPlay() override;
	virtual void CalculateMove(bool bDrawRender) override;

public:

	bool bInCheck = false;

protected:

	TArray<FIntVector2> m_KingMoves{{0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,-1},{-1, 1},{1,-1}};
	
	TArray<AChessPiece*> m_CheckedPieces;

private:
};
