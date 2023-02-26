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
        UE_LOG(LogTemp, Error, TEXT("Gamemode was null in a %s"), *GetName());
        return;
    }

    m_gameBoard = m_Gamemode->GetChessBoard();

    if (m_gameBoard == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Gameboard was null in a %s"), *GetName());
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
        if (m_Distance == 0)
        {
            m_Distance = 1;
            movePercent = 1;
        }
        movePercent += DeltaTime * MovementSpeed / m_Distance;
        movePercent = FMath::Clamp(movePercent, 0, 1);

        float z = FMath::Lerp(0.0f, 10.0f, 4 * (movePercent - movePercent * movePercent));

        SetActorLocation(FMath::Lerp(StartPos, newLocation, (1 + FMath::Cos(PI * (movePercent + 1))) / 2) + FVector::UpVector * z);

        if (movePercent >= 1)
        {
            bMovePiece = false;
            movePercent = 0;
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

EPieceType AChessPiece::GetPieceType()
{
    if (m_PieceType == -1)
    {
        UE_LOG(LogTemp, Error, TEXT("m_PieceType was null at %s"), *GetName());
    }

    return m_PieceType;
}

void AChessPiece::MovePiece(AChessBoardCell* selectedCell)
{
    if (m_Gamemode->GetCurrentTeam() != m_CurrentTeam) { return; }
    bMovePiece = true;
    newLocation = selectedCell->GetMiddleOfCell();
    StartPos = GetActorLocation();
    m_Distance = FVector::Distance(StartPos, newLocation);
    m_Distance = (m_Distance / 1000 + 1) * 0.5f;

    m_CurrentCell->SetChessPieceOnCell(nullptr);
    m_CurrentCell = selectedCell;
    m_CurrentCell->SetChessPieceOnCell(this);

    m_CurrentCell->GetIndex(m_xIndex, m_yIndex);

    PieceUnselected();
    CheckNextMove();
    if (m_Gamemode->GetCurrentTeam() == EPieceTeam::Empty) { return; }
    if (!bCastling)
    {
        m_Gamemode->SetCurrentTeam(m_CurrentTeam);
    }
}

bool AChessPiece::IsCellEmpty(int xIndex, int yIndex)
{
    return m_gameBoard->GetCellAtIndex(xIndex, yIndex)->GetChessPieceOnCell() == nullptr;
}

void AChessPiece::KillPiece(AChessBoardCell* selectedCell)
{
    FVector loc = m_Gamemode->GetDeadPieceLocation(m_CurrentTeam);
    AChessPiece* killingPiece = selectedCell->GetChessPieceOnCell();
    if (killingPiece == nullptr) { return; }
    killingPiece->KillMovement();
    killingPiece->SetActorLocation(loc);
    killingPiece->bIsAlive = false;
    killingPiece->SetCurrentCell(nullptr);
    selectedCell->SetChessPieceOnCell(nullptr);
    loc.X += 30 * m_teamDir;
    m_Gamemode->RemovePieceFromTeam(m_OppositeTeam, killingPiece);
    m_Gamemode->SetDeadPieceLocation(m_CurrentTeam, loc);
}

void AChessPiece::PieceSelected()
{
    if (m_Gamemode->GetCurrentTeam() != m_CurrentTeam)
    {
        return;
    }
    if (!bIsAlive) { return; }

    bIsSelected = true;
    m_moveableCells.Empty();
    CalculateMove(true);
}

void AChessPiece::PieceUnselected()
{
    if (m_moveableCells.Num() == 0) { return; }

    for (auto moveableCell : m_moveableCells)
    {
        moveableCell->SetSelectedMaterial(0, true);
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
    if (m_Gamemode->GetCurrentTeam() != m_CurrentTeam) { return; }

    int SCX, SCY;
    selectedCell->GetIndex(SCX, SCY);
    AChessBoardCell* savedCell = m_CurrentCell;

    for (auto moveableCell : m_moveableCells)
    {
        if (selectedCell == moveableCell)
        {
            if (IsCellEmpty(SCX, SCY))
            {
                selectedCell->SetChessPieceOnCell(this);
                m_CurrentCell->SetChessPieceOnCell(nullptr);
                if (m_Gamemode->GetTeamInCheck(m_CurrentTeam) == true && m_Gamemode->IsKingStillInCheck(m_CurrentTeam, selectedCell, m_PieceType))
                {
                    selectedCell->SetChessPieceOnCell(nullptr);
                    m_CurrentCell->SetChessPieceOnCell(this);
                    break;
                }
                selectedCell->SetChessPieceOnCell(nullptr);
                m_CurrentCell->SetChessPieceOnCell(this);
            }
            if (selectedCell->GetChessPieceOnCell() != nullptr)
            {
                AChessPiece* tempPiece = selectedCell->GetChessPieceOnCell();
                m_CurrentCell->SetChessPieceOnCell(nullptr);
                tempPiece->bIsAlive = false;
                if (m_Gamemode->GetTeamInCheck(m_CurrentTeam) == true && m_Gamemode->IsKingStillInCheck(m_CurrentTeam, selectedCell, m_PieceType))
                {
                    m_CurrentCell->SetChessPieceOnCell(this);
                    selectedCell->SetChessPieceOnCell(tempPiece);
                    tempPiece->bIsAlive = true;
                    break;
                }
                m_CurrentCell->SetChessPieceOnCell(this);
                selectedCell->SetChessPieceOnCell(tempPiece);
                KillPiece(selectedCell);
            }
            MovePiece(selectedCell);
            m_Gamemode->SetTeamInCheck(m_CurrentTeam, false);
            break;
        }
    }
}

void AChessPiece::KillMovement()
{
    bMovePiece = false;
}


