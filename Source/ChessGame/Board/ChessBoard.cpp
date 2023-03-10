// Fill out your copyright notice in the Description page of Project Settings.


#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"
#include "../Managers/ChessGameModeBase.h"
#include "../Pieces/ChessPiece.h"
#include "../Pieces/Ch_KingPiece.h"

// Sets default values
AChessBoard::AChessBoard()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{
    Super::BeginPlay();

    m_Gamemode = Cast<AChessGameModeBase>(GetWorld()->GetAuthGameMode());
    if (m_Gamemode)
    {
        m_Gamemode->SetChessBoard(this);
    }

    CreateBoard();
}

void AChessBoard::CreateBoard()
{
    for (int x = 0; x < boardX; x++)
    {
        for (int y = 0; y < boardY; y++)
        {
            FActorSpawnParameters SpawnParams;
            int SpawnLocX = x * cellSpace;
            int SpawnLocY = y * cellSpace;
            FVector SpawnLocation = FVector(SpawnLocX, SpawnLocY, 0);
            FRotator SpawnRot = FRotator(0, 0, 0);
            AChessBoardCell* tempActor = GetWorld()->SpawnActor<AChessBoardCell>(CellToSpawn, SpawnLocation, SpawnRot, SpawnParams);
            tempActor->SetIndex(x, y);

            if ((x + y) % 2)
            {
                tempActor->SetDefaultMaterial(1);
            }

            ChessGrid[x][y] = tempActor;
            if (x == 0 || x == 7)
            {
                SpawnPieces(tempActor, x, y);
            }
            if (x == 1 || x == 6)
            {
                SpawnPawns(tempActor, x);
            }
        }
    }

    SpawnExtraPieces();
}

void AChessBoard::SpawnPawns(AChessBoardCell* cell, int xIndex)
{
    FActorSpawnParameters Parms;
    FVector SpawnLocation = cell->GetMiddleOfCell();
    FRotator SpawnRot = FRotator(0, 0, 0);

    AChessPiece* tempPiece = GetWorld()->SpawnActor<AChessPiece>(PawnPiecesToSpawn[0], SpawnLocation, SpawnRot, Parms);
    cell->SetChessPieceOnCell(tempPiece);
    tempPiece->SetCurrentCell(cell);

   

    AChessGameModeBase* GM;
    GM = Cast<AChessGameModeBase>(GetWorld()->GetAuthGameMode());
 

    switch (xIndex)
    {
    case 1:
        tempPiece->SetTeam(EPieceTeam::White);    
        GM->AliveWhiteTeam.Add(tempPiece);
        break;
    case 6:
        tempPiece->SetTeam(EPieceTeam::Black);
        GM->AliveBlackTeam.Add(tempPiece);
        break;
    default:
        tempPiece->SetTeam(EPieceTeam::White);
        GM->AliveWhiteTeam.Add(tempPiece);
        break;
    }
}

void AChessBoard::SpawnPieces(AChessBoardCell* cell, int xIndex, int typeIndex)
{
    int spawnIndex;
    switch (typeIndex)
    {
    case 0:
        spawnIndex = 1;
        break;
    case 1:
        spawnIndex = 2;
        break;
    case 2:
        spawnIndex = 3;
        break;
    case 3:
        spawnIndex = 5;
        break;
    case 4:
        spawnIndex = 4;
        break;
    case 5:
        spawnIndex = 3;
        break;
    case 6:
        spawnIndex = 2;
        break;
    case 7:
        spawnIndex = 1;
        break;
    default:
        spawnIndex = 1;
        break;
    }

    FActorSpawnParameters Parms;
    FVector SpawnLocation = cell->GetMiddleOfCell();
    FRotator SpawnRot = FRotator(0, 0, 0);

    AChessPiece* tempPiece = GetWorld()->SpawnActor<AChessPiece>(PawnPiecesToSpawn[spawnIndex], SpawnLocation, SpawnRot, Parms);
    cell->SetChessPieceOnCell(tempPiece);
    tempPiece->SetCurrentCell(cell);

    AChessGameModeBase* GM;
    GM = Cast<AChessGameModeBase>(GetWorld()->GetAuthGameMode());
  
    switch (xIndex)
    {
    case 0:
        tempPiece->SetTeam(EPieceTeam::White);    
        GM->AliveWhiteTeam.Add(tempPiece);
        if (tempPiece->GetPieceType() == EPieceType::King)
        {
            GM->whiteKingPiece = Cast<ACh_KingPiece>(tempPiece);
        }
        break;
    case 7:
        tempPiece->SetTeam(EPieceTeam::Black);
        GM->AliveBlackTeam.Add(tempPiece);
        if (tempPiece->GetPieceType() == EPieceType::King)
        {
            GM->blackKingPiece = Cast<ACh_KingPiece>(tempPiece);
        }
        break;
    default:
        tempPiece->SetTeam(EPieceTeam::White);
        GM->AliveWhiteTeam.Add(tempPiece);
        break;
    }
}

void AChessBoard::SpawnExtraPieces()
{
    FActorSpawnParameters Parms;
    FVector SpawnLoc = FVector(0.0f, 0.0f, 10000.0f);
    FRotator SpawnRot = FRotator(0, 0, 0);

    for (int i = 1; i < 5; i++)
    {
        for (int k = 0; k < 16; k++)
        {
            AChessPiece* tempPiece = GetWorld()->SpawnActor<AChessPiece>(PawnPiecesToSpawn[i], SpawnLoc, SpawnRot, Parms);
            m_Gamemode->ExtraPieces.Add(tempPiece);
        }
    }
}

// Called every frame
void AChessBoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AChessBoard::GetBoardSize(int& xSize, int& ySize)
{
    xSize = boardX;
    ySize = boardY;
}

FVector AChessBoard::GetCellLocation(int x, int y)
{
    return ChessGrid[x][y]->GetActorLocation();
}

AChessBoardCell* AChessBoard::GetCellAtIndex(int xIndex, int yIndex)
{
    if (xIndex < boardX && yIndex < boardY && xIndex >= 0 && yIndex >= 0)
    {
        return ChessGrid[xIndex][yIndex];
    }


    return nullptr;
}

