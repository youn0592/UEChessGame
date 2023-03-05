// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChessMenuGamemode.generated.h"

/**
 * 
 */

class ACh_MainMenuHUD;

UCLASS()
class CHESSGAME_API AChessMenuGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AChessMenuGamemode();

	void PlayGame();
	void QuitGame();

protected:

	virtual void BeginPlay() override;

public:

protected:

	ACh_MainMenuHUD* m_MenuHUD;
private:


	
};
