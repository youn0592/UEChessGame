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

	
protected:

	virtual void BeginPlay() override;

public:

protected:

	AChessBoard* m_ChessBoard;
	EPieceTeam m_CurrentTeam;

private:


};
