// Fill out your copyright notice in the Description page of Project Settings.


#include "../Board/ChessBoardCell.h"
#include "../Pieces/ChessPiece.h"

// Sets default values
AChessBoardCell::AChessBoardCell()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CellMesh = CreateDefaultSubobject<UStaticMeshComponent>("CellMesh");
    RootComponent = CellMesh;

    SelectMesh = CreateDefaultSubobject<UStaticMeshComponent>("SelectMesh");
    SelectMesh->SetupAttachment(RootComponent);

    Tags.Add("BoardCell");
}

// Called when the game starts or when spawned
void AChessBoardCell::BeginPlay()
{
    Super::BeginPlay();

    m_CellDefaultMaterial = m_DefaultMaterials[0];

}

// Called every frame
void AChessBoardCell::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AChessBoardCell::SetDefaultMaterial(int index)
{
    m_CellDefaultMaterial = m_DefaultMaterials[index];
    CellMesh->SetMaterial(0, m_DefaultMaterials[index]);
}

void AChessBoardCell::SetMaterial(int index)
{
    CellMesh->SetMaterial(0, m_DefaultMaterials[index]);
}

void AChessBoardCell::SetSelectedMaterial(int index)
{
    SelectMesh->SetMaterial(0, m_SelectedMaterials[index]);
}

void AChessBoardCell::ResetMaterial()
{
    CellMesh->SetMaterial(0, m_CellDefaultMaterial);
}

void AChessBoardCell::SetChessPieceOnCell(AChessPiece* ChessPiece)
{
    m_PieceOnCell = ChessPiece;
}

AChessPiece* AChessBoardCell::GetChessPieceOnCell()
{
    if (!m_PieceOnCell) { return nullptr; }

    return m_PieceOnCell;
}

bool AChessBoardCell::IsKingOnCell()
{
    if (!m_PieceOnCell) { return false; }

    if (m_PieceOnCell->GetPieceType() == EPieceType::King)
    {
        return true;
    }

    return false;

}

FVector AChessBoardCell::GetMiddleOfCell()
{
    float halfSize = CellMesh->GetRelativeScale3D().X;
    halfSize *= (GetActorScale3D().X * 100);
    FVector cellMiddle = GetActorLocation() + (halfSize, halfSize, 0);
    return cellMiddle;
}

void AChessBoardCell::SetIndex(int xIndex, int yIndex)
{
    m_indexX = xIndex;
    m_indexY = yIndex;
}

void AChessBoardCell::GetIndex(int& xIndex, int& yIndex)
{
    xIndex = m_indexX;
    yIndex = m_indexY;
}


