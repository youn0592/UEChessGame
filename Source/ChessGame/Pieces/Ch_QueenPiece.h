// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pieces/ChessPiece.h"
#include "Ch_QueenPiece.generated.h"

/**
 * 
 */
UCLASS()
class CHESSGAME_API ACh_QueenPiece : public AChessPiece
{
	GENERATED_BODY()

public:

	ACh_QueenPiece();

	virtual void Tick(float DeltaTime) override;

	virtual TArray<AChessBoardCell*> CheckNextMove() override;

protected:

	virtual void BeginPlay() override;

	virtual void CalculateMove(bool bDrawRender) override;

public:
protected:
private:
	
};
