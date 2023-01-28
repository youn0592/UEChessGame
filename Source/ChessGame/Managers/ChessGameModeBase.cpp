// Fill out your copyright notice in the Description page of Project Settings.


#include "../Managers/ChessGameModeBase.h"
#include "../Board/ChessBoard.h"


AChessGameModeBase::AChessGameModeBase()
{
}

void AChessGameModeBase::BeginPlay()
{    
    Super::BeginPlay();

}

void AChessGameModeBase::SetChessBoard(AChessBoard* newBoard)
{
    m_ChessBoard = newBoard;
}

AChessBoard* AChessGameModeBase::GetChessBoard()
{
    return m_ChessBoard;
}

