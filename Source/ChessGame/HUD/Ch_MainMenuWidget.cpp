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

    PlayButton->OnClicked.AddUniqueDynamic(this, &UCh_MainMenuWidget::PlayGame);
    CreditButton->OnClicked.AddUniqueDynamic(this, &UCh_MainMenuWidget::CreditSelected);
    QuitButton->OnClicked.AddUniqueDynamic(this, &UCh_MainMenuWidget::QuitGame);
}

void UCh_MainMenuWidget::PlayGame()
{
    m_Gamemode->PlayGame();
}

void UCh_MainMenuWidget::CreditSelected()
{
    return;
}

void UCh_MainMenuWidget::QuitGame()
{
    m_Gamemode->QuitGame();
}
