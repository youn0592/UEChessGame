// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../ChessGame.h"
#include "ChessBoard.generated.h"

class AChessPiece;
class AChessBoardCell;

UCLASS()
class CHESSGAME_API AChessBoard : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AChessBoard();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetBoardSize(int& xSize, int& ySize);
	FVector GetCellLocation(int x, int y);
	AChessBoardCell* GetCellAtIndex(int xIndex, int yIndex);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CreateBoard();
	UFUNCTION()
	void SpawnPawns(AChessBoardCell* cell, int xIndex);

	UFUNCTION()
	void SpawnPieces(AChessBoardCell* cell, int xIndex, int yIndex);

public:	

protected:
	static const int boardX = 8;
	static const int boardY = 8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	int cellSpace = 50;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> CellToSpawn;

	AChessBoardCell* ChessGrid[boardX][boardY];

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<TSubclassOf<AChessPiece>> PawnPiecesToSpawn;

private:


};
