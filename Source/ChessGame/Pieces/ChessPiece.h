// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ChessGame.h"
#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

class UBoxComponent;
class AChessBoardCell;
class AChessBoard;
class AChessGameModeBase;


//Parent Class for all Chess Pieces
UCLASS()
class CHESSGAME_API AChessPiece : public AActor
{
    GENERATED_BODY()

public:

    // Sets default values for this actor's properties
    AChessPiece();

    virtual void SetTeam(EPieceTeam team);
    virtual EPieceTeam GetTeam();
    virtual EPieceType GetPieceType();

    virtual void PieceSelected();
    virtual void PieceUnselected();

    virtual void SetCurrentCell(AChessBoardCell* newCell);
    virtual AChessBoardCell* GetCurrentCell();
    
    virtual void CheckSelectedCell(AChessBoardCell* selectedCell);

    virtual TArray<AChessBoardCell*> CheckNextMove() { return TArray<AChessBoardCell*>(); };

    virtual void KillMovement();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void CalculateMove(bool bDrawRender) {};
    virtual void MovePiece(AChessBoardCell* selectedCell);

    virtual bool IsCellEmpty(int xIndex, int yIndex);

public:

    bool bIsAlive;

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
        USceneComponent* m_RootComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
        UMeshComponent* m_ChessPieceMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
        UBoxComponent* m_BoxCollision;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
        TArray<UMaterial*> m_PieceMaterials;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
        float MovementSpeed = 2.0f;

    bool bIsSelected, bMovePiece;
    FVector newLocation;

    EPieceTeam m_CurrentTeam;
    EPieceTeam m_OppositeTeam;
    EPieceType m_PieceType;

    AChessBoardCell* m_CurrentCell;
    TArray<AChessBoardCell*> m_moveableCells;

    AChessBoard* m_gameBoard;

    int m_boardSizeX, m_boardSizeY;
    int m_xIndex, m_yIndex;
    int m_teamDir;
    float m_Distance;

    FVector StartPos;
    FVector LastFramePos;
    AChessGameModeBase* m_Gamemode;

private:

    float movePercent;

};
