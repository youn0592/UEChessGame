// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessBoardCell.generated.h"

UCLASS()
class CHESSGAME_API AChessBoardCell : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AChessBoardCell();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void SetDefaultMaterial(int index);
    void SetSelectedMaterial(int index, bool bDrawRender);
    void ResetMaterial();

    void SetChessPieceOnCell(class AChessPiece* ChessPiece);
    AChessPiece* GetChessPieceOnCell();
    bool IsKingOnCell();

    FVector GetMiddleOfCell();

    void SetIndex(int xIndex, int yIndex);
    void GetIndex(int& xIndex,  int& yIndex);

    int GetX() { return m_indexX; }
    int GetY() { return m_indexY; }

protected:

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
        UStaticMeshComponent* CellMesh;    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
        UStaticMeshComponent* SelectMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
        TArray<UMaterial*> m_DefaultMaterials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
        TArray<UMaterial*> m_SelectedMaterials;

    UMaterial* m_CellDefaultMaterial;

    AChessPiece* m_PieceOnCell;
    FVector CellCenter;

    int m_indexX, m_indexY;


private:


};
