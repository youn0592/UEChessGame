// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ChessGameStateBase.generated.h"

/**
 * 
 */

class AChessPiece;

UCLASS()
class CHESSGAME_API AChessGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:

protected:

	virtual void BeginPlay() override;

public:



protected:

private:
	
};
