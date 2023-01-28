// Fill out your copyright notice in the Description page of Project Settings.


#include "../Managers/ChessPlayerController.h"
#include "../Managers/ChessCamera.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


void AChessPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    CurrentMousePos = FVector2D(0.0f, 0.0f);

    if (UEnhancedInputLocalPlayerSubsystem* Sub = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Sub->AddMappingContext(PlayerMapping, 0);
    }
}

void AChessPlayerController::AcknowledgePossession(APawn* inPawn)
{
    Super::AcknowledgePossession(inPawn);

    ControlledCamera = Cast<AChessCamera>(inPawn);
}


void AChessPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
    {
        Input->BindAction(LeftClickAction, ETriggerEvent::Triggered, this, &AChessPlayerController::HandleLeftClick);
        Input->BindAction(RightClickAction, ETriggerEvent::Triggered, this, &AChessPlayerController::HandleRightClick);
        Input->BindAction(MousePosAction, ETriggerEvent::None, this, &AChessPlayerController::HandleMousePosition);
    }


}

void AChessPlayerController::HandleLeftClick(const FInputActionValue& Instance)
{
    const bool LeftClickValue = Instance.Get<bool>();
    if (!LeftClickValue)
    {
        UE_LOG(LogTemp, Error, TEXT("Left Click Value is Null"));
        return;
    }
    FVector MousePosition;
    FVector MouseDirection;

    DeprojectMousePositionToWorld(MousePosition, MouseDirection);
    ControlledCamera->LeftClickTriggered(MousePosition);

}

void AChessPlayerController::HandleRightClick(const FInputActionValue& Instance)
{
    const bool RightClickValue = Instance.Get<bool>();
    if (!RightClickAction)
    {
        UE_LOG(LogTemp, Error, TEXT("Right Click Valule is Null"));
        return;
    }


}

void AChessPlayerController::HandleMousePosition(const FInputActionValue& Instance)
{
    FVector2D AxisValue = Instance.Get<FVector2D>();

    GetMousePosition(CurrentMousePos.X, CurrentMousePos.Y);


/*    UE_LOG(LogTemp, Warning, TEXT("MousePos: %f , %f"), CurrentMousePos.X, CurrentMousePos.Y)*/;

}
