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


void AChessPiece::BeginPlay()
{
    Super::BeginPlay();

    m_Gamemode = Cast<AChessGameModeBase>(GetWorld()->GetAuthGameMode());
    if (m_Gamemode == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode was null in PawnPiece"));
        return;
    }

    m_gameBoard = m_Gamemode->GetChessBoard();

    if (m_gameBoard == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("m_gameBoard was null in PawnPiece"));
        return;
    }

    m_gameBoard->GetBoardSize(m_boardSizeX, m_boardSizeY);
    bIsAlive = true;
}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bMovePiece)
    {    
        LastFramePos = GetActorLocation();
        SetActorLocation(FMath::Lerp(GetActorLocation(), newLocation, MovementSpeed * DeltaTime));
        if (LastFramePos == GetActorLocation())
        {
            bMovePiece = false;
        }
    }
}

void AChessPiece::SetTeam(EPieceTeam team)
{
    if (!m_PieceMaterials[team])
    {
        UE_LOG(LogTemp, Error, TEXT("Materials was nullptr in ChessPiece"));
    }

    switch (team)
    {
    case EPieceTeam::White:
        m_CurrentTeam = team;
        m_OppositeTeam = EPieceTeam::Black;
        m_teamDir = 1;
        break;
    case EPieceTeam::Black:
        m_CurrentTeam = team;
        m_ChessPieceMesh->AddRelativeRotation(FRotator(0, 180, 0));
        m_teamDir = -1;
        m_OppositeTeam = EPieceTeam::White;
        break;
    default:
        break;
    }

    m_ChessPieceMesh->SetMaterial(0, m_PieceMaterials[team]);
    return;
}

EPieceTeam AChessPiece::GetTeam()
{
    return m_CurrentTeam;
}

void AChessPiece::CalculateMove()
{
}

void AChessPiece::MovePiece(AChessBoardCell* selectedCell)
{
    if (m_Gamemode->GetCurrentTeam() != m_CurrentTeam) { return; }
    bMovePiece = true;
    newLocation = selectedCell->GetMiddleOfCell();

    m_CurrentCell->SetChessPieceOnCell(nullptr);
    m_CurrentCell = selectedCell;
    m_CurrentCell->SetChessPieceOnCell(this);

    m_CurrentCell->GetIndex(m_xIndex, m_yIndex);

    m_Gamemode->SetCurrentTeam(m_CurrentTeam);
    PieceUnselected();
}

bool AChessPiece::IsCellEmpty(int xIndex, int yIndex)
{
    return m_gameBoard->GetCellAtIndex(xIndex, yIndex)->GetChessPieceOnCell() == nullptr;
}

void AChessPiece::PieceSelected()
{
    if (m_Gamemode->GetCurrentTeam() != m_CurrentTeam)
    {
        return;
    }
    if (!bIsAlive) { return; }
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

    if (m_CurrentCell)
    {
        m_CurrentCell->GetIndex(m_xIndex, m_yIndex);
    }
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
            if (selectedCell->GetChessPieceOnCell() != nullptr)
            {
                //Will Change
                FVector loc = m_Gamemode->GetDeadPieceLocation(m_CurrentTeam);
                selectedCell->GetChessPieceOnCell()->KillMovement();
                selectedCell->GetChessPieceOnCell()->SetActorLocation(loc);
                selectedCell->GetChessPieceOnCell()->bIsAlive = false;
                selectedCell->GetChessPieceOnCell()->SetCurrentCell(nullptr);
                selectedCell->SetChessPieceOnCell(nullptr);
                loc.X += 25 * m_teamDir;
                m_Gamemode->SetDeadPieceLocation(m_CurrentTeam, loc);
            }
            MovePiece(selectedCell);
        }
    }
}

void AChessPiece::KillMovement()
{
    bMovePiece = false;
}


