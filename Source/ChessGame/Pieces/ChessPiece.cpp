// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pieces/ChessPiece.h"
#include "Components/BoxComponent.h"
#include "../Managers/ChessGameModeBase.h"
#include "../Board/ChessBoard.h"
#include "../Board/ChessBoardCell.h"

// Sets default values
AChessPiece::AChessPiece()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    m_RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
    RootComponent = m_RootComponent;

    m_ChessPieceMesh = CreateDefaultSubobject<UStaticMeshComponent>("PieceMesh");
    m_ChessPieceMesh->SetupAttachment(RootComponent);

    m_BoxCollision = CreateDefaultSubobject<UBoxComponent>("PieceCollision");
    m_BoxCollision->SetupAttachment(RootComponent);

    Tags.Add("ChessPiece");
}

void AChessPiece::SetTeam(EPieceTeam team)
{
    if (!m_PieceMaterials[team])
    {
        UE_LOG(LogTemp, Error, TEXT("Materials was nullptr in ChessPiece"));
    }

    CurrentTeam = team;
    m_ChessPieceMesh->SetMaterial(0, m_PieceMaterials[team]);
    return;
}

void AChessPiece::BeginPlay()
{
    Super::BeginPlay();


    AChessGameModeBase* GM = Cast<AChessGameModeBase>(GetWorld()->GetAuthGameMode());
    if (GM == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode was null in PawnPiece"));
        return;
    }

    m_gameBoard = GM->GetChessBoard();

    if (m_gameBoard == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("m_gameBoard was null in PawnPiece"));
        return;
    }

    m_gameBoard->GetBoardSize(m_boardSizeX, m_boardSizeY);

    //m_BoxCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bMovePiece)
    {
        SetActorLocation(FMath::Lerp(GetActorLocation(), newLocation, MovementSpeed * DeltaTime));
    }
}

void AChessPiece::CalculateMove()
{
}

void AChessPiece::MovePiece(AChessBoardCell* selectedCell)
{
    bMovePiece = true;
    newLocation = selectedCell->GetMiddleOfCell();

    m_CurrentCell->SetChessPieceOnCell(nullptr);
    m_CurrentCell = selectedCell;
    m_CurrentCell->SetChessPieceOnCell(this);

    m_CurrentCell->GetIndex(m_xIndex, m_yIndex);
    PieceUnselected();
}

bool AChessPiece::IsCellEmpty(int xIndex, int yIndex)
{
    return m_gameBoard->GetCellAtIndex(xIndex, yIndex)->GetChessPieceOnCell() == nullptr;
}

void AChessPiece::PieceSelected()
{
    bIsSelected = true;
    CalculateMove();
}

void AChessPiece::PieceUnselected()
{
    if (m_moveableCells.Num() == 0) { return; }

    for (int i = 0; i < m_moveableCells.Num(); i++)
    {
        m_moveableCells[i]->SetSelectedMaterial(0);
    }
    m_moveableCells.Empty();
    bIsSelected = false;
}

void AChessPiece::SetCurrentCell(AChessBoardCell* newCell)
{
    m_CurrentCell = newCell;
    m_CurrentCell->GetIndex(m_xIndex, m_yIndex);
}

AChessBoardCell* AChessPiece::GetCurrentCell()
{
    return m_CurrentCell;
}

void AChessPiece::CheckSelectedCell(AChessBoardCell* selectedCell)
{
    if (m_moveableCells.Num() == 0) { return; }

    int SCX, SCY;
    selectedCell->GetIndex(SCX, SCY);

    for (int i = 0; i < m_moveableCells.Num(); i++)
    {
        if (selectedCell == m_moveableCells[i])
        {
            int curX, curY;
            m_CurrentCell->GetIndex(curX, curY);
            MovePiece(selectedCell);
        }
    }
}


