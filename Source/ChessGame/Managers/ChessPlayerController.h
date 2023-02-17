// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "ChessPlayerController.generated.h"

/**
 *
 */
class AChessCamera;
class UInputMappingContext;
class UInputAction;

UCLASS()
class CHESSGAME_API AChessPlayerController : public APlayerController
{
    GENERATED_BODY()

public:

    virtual void BeginPlay() override;
    virtual void AcknowledgePossession(APawn* inPawn) override;

protected:

    virtual void SetupInputComponent() override;

    void HandleLeftClick(const FInputActionValue& Instance);
    void HandleRightClick(const FInputActionValue& Instance);
    void HandleMouseWheel(const FInputActionValue& Instance);
    void HandleMousePosition(const FInputActionValue& Instance);
    void HandleADInput(const FInputActionValue& Instance);

public:

protected:


    AChessCamera* ControlledCamera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
        UInputMappingContext* PlayerMapping;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
        UInputAction* LeftClickAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
        UInputAction* RightClickAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
        UInputAction* MousePosAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
        UInputAction* MouseScrollWheel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
        UInputAction* ADKeyboardAction;

private:

    FVector2D CurrentMousePos;
};
