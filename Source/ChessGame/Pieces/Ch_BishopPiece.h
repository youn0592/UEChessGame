// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pieces/ChessPiece.h"
#include "Ch_BishopPiece.generated.h"

/**
 * 
 */
UCLASS()
class CHESSGAME_API ACh_BishopPiece : public AChessPiece
{
	GENERATED_BODY()

public:

	ACh_BishopPiece();

	virtual void Tick(float DeltaTime) override;

	virtual TArray<AChessBoardCell*> CheckNextMove() override;
	virtual void CheckForCheck() override;

protected:

	virtual void BeginPlay() override;

	virtual void CalculateMove() override;

public:
protected:
private:
};
