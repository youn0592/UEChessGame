// Fill out your copyright notice in the Description page of Project Settings.


#include "../Managers/ChessMenuGamemode.h"
#include "../HUD/Ch_MainMenuHUD.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AChessMenuGamemode::AChessMenuGamemode()
{
}

void AChessMenuGamemode::BeginPlay()
{
    Super::BeginPlay();

    m_MenuHUD = Cast<ACh_MainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
    if (m_MenuHUD == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Menu was null in MainMenu Gamemode"));
    }
}

void AChessMenuGamemode::PlayGame()
{
    UGameplayStatics::OpenLevel(this, FName("MainChessScene"), false);
}

void AChessMenuGamemode::QuitGame()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

