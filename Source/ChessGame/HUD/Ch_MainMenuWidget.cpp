// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/Ch_MainMenuWidget.h"
#include "../Managers/ChessMenuGamemode.h"
#include <Components/Button.h>

void UCh_MainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    m_Gamemode = Cast<AChessMenuGamemode>(GetWorld()->GetAuthGameMode());
    if (m_Gamemode == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Gamemode was null in MainMenuWidget"));
    }

    CreditsPanel->SetVisibility(ESlateVisibility::Hidden);

    PlayOnlineButton->OnClicked.AddUniqueDynamic(this, &UCh_MainMenuWidget::PlayOnlineGame);
    PlayButton->OnClicked.AddUniqueDynamic(this, &UCh_MainMenuWidget::PlayGame);
    CreditButton->OnClicked.AddUniqueDynamic(this, &UCh_MainMenuWidget::CreditSelected);
    QuitButton->OnClicked.AddUniqueDynamic(this, &UCh_MainMenuWidget::QuitGame);
    BackButton->OnClicked.AddUniqueDynamic(this, &UCh_MainMenuWidget::BackSelected);
}

void UCh_MainMenuWidget::PlayOnlineGame()
{
    //TODO - Setup the ability to open a Lobby which allows the player to invite friends from friends list and choose which colour to start as.
    m_Gamemode->PlayGame();
}

//Function for playing Local game
void UCh_MainMenuWidget::PlayGame()
{
    m_Gamemode->PlayGame();
}

void UCh_MainMenuWidget::CreditSelected()
{
    MainMenuPanel->SetVisibility(ESlateVisibility::Hidden);
    CreditsPanel->SetVisibility(ESlateVisibility::Visible);
}

void UCh_MainMenuWidget::QuitGame()
{
    m_Gamemode->QuitGame();
}

void UCh_MainMenuWidget::BackSelected()
{
    MainMenuPanel->SetVisibility(ESlateVisibility::Visible);
    CreditsPanel->SetVisibility(ESlateVisibility::Hidden);
}
