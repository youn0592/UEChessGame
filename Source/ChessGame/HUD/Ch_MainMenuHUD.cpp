// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/Ch_MainMenuHUD.h"
#include "../HUD/Ch_MainMenuWidget.h"

ACh_MainMenuHUD::ACh_MainMenuHUD()
{
}

void ACh_MainMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (BP_MainMenuWidget)
    {
        m_MainMenuWidget = CreateWidget<UCh_MainMenuWidget>(GetWorld(), BP_MainMenuWidget);
        m_MainMenuWidget->AddToViewport();
    }
}

void ACh_MainMenuHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACh_MainMenuHUD::DrawHUD()
{
    Super::DrawHUD();
}

