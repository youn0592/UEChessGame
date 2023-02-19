// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/Ch_ChessHUD.h"
#include "../HUD/Ch_OnScreenWidget.h"
#include "Components/WidgetComponent.h"

ACh_ChessHUD::ACh_ChessHUD()
{

}

void ACh_ChessHUD::BeginPlay()
{
    Super::BeginPlay();

    if (BP_OnScreenWidget)
    {
        m_OnScreenWidget = CreateWidget<UCh_OnScreenWidget>(GetWorld(), BP_OnScreenWidget);
        m_OnScreenWidget->AddToViewport();
    }
}

void ACh_ChessHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACh_ChessHUD::DrawHUD()
{
    Super::DrawHUD();
}

void ACh_ChessHUD::ShowPawnPopupWindow(bool bActive)
{
    if (m_OnScreenWidget == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("m_OnScreenWidget was Null in ChessHUD"));
        return;
    }
    m_OnScreenWidget->SetPopupWindow(bActive);
}

void ACh_ChessHUD::SetCurrentTeam(EPieceTeam currentTeam)
{
    if (m_OnScreenWidget == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("m_OnScreenWidget was Null in ChessHUD"));
        return;
    }

    FString currentTeamName;

    switch (currentTeam)
    {
    case EPieceTeam::White:
        currentTeamName = "White";
        break;
    case EPieceTeam::Black:
        currentTeamName = "Black";
        break;
    }

    m_OnScreenWidget->SetCurrentTeam(currentTeamName);

}

void ACh_ChessHUD::SetTeamInCheck(EPieceTeam currentTeam, bool bActive)
{
    if (m_OnScreenWidget == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("m_OnScreenWidget was Null in ChessHUD"));
        return;
    }

    FString currentTeamName;

    switch (currentTeam)
    {
    case EPieceTeam::White:
        currentTeamName = "White King";
        break;
    case EPieceTeam::Black:
        currentTeamName = "Black King";
        break;
    }

    m_OnScreenWidget->SetTeamInCheck(currentTeamName, bActive);
}

void ACh_ChessHUD::SetCheckMate(EPieceTeam losingTeam)
{
    FString winningTeamName;
    switch (losingTeam)
    {
    case EPieceTeam::White:
        winningTeamName = "Black Team Wins";
        break;
    case EPieceTeam::Black:
        winningTeamName = "White Team Wins";
        break;
    }

    m_OnScreenWidget->SetCheckmatePanel(winningTeamName);
}

