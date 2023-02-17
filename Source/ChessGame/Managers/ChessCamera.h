// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ChessCamera.generated.h"

class AChessPiece;
class AChessGameModeBase;

UCLASS()
class CHESSGAME_API AChessCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AChessCamera();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LeftClickTriggered(FVector MousePos);
	void MouseWheelSpun(float wheelValue);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* MainCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class USpringArmComponent* CameraArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		USceneComponent* ForwardCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float DistanceFromCamera = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float m_MouseSpeed = 3.0f;


private: 

	APlayerController* playerController;
	AChessPiece* LastSelectedPiece;
	AChessGameModeBase* m_Gamemode;

};
