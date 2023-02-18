// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/Ch_OnScreenWidget.h"
#include "../HUD/Ch_PawnPopupWidget.h"
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include <Components/Image.h>
#include <Components/CanvasPanel.h>

void UCh_OnScreenWidget::NativeConstruct()
{
    Super::NativeConstruct();

    PawnPopupWindow->SetIsEnabled(false);
    PawnPopupWindow->SetVisibility(ESlateVisibility::Hidden);

    CheckTextVBox->SetVisibility(ESlateVisibility::Hidden);
    CheckmatePanel->SetVisibility(ESlateVisibility::Hidden);
    IconImage->SetBrushFromAsset(UiImages[0]);
}

void UCh_OnScreenWidget::SetPopupWindow(bool bActive)
{
    if (PawnPopupWindow == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("PawnPopupWindow was null in OnScreenWidget"));
        return;
    }
    PawnPopupWindow->SetIsEnabled(bActive);
    ESlateVisibility currentVisibilty;

    switch (bActive)
    {
    case true:
        currentVisibilty = ESlateVisibility::Visible;
        break;
    case false:
        currentVisibilty = ESlateVisibility::Hidden;
        break;
    }

    PawnPopupWindow->SetVisibility(currentVisibilty);
}

void UCh_OnScreenWidget::SetCurrentTeam(FString name)
{
    bIsWhiteTeam = !bIsWhiteTeam;
    IconImage->SetBrushFromAsset(UiImages[bIsWhiteTeam]);
    TurnMoveBlock->SetText(FText::FromString(name));
}

void UCh_OnScreenWidget::SetTeamInCheck(FString name, bool bActive)
{
    ESlateVisibility currentVisibilty;
    switch (bActive)
    {
    case true:
        currentVisibilty = ESlateVisibility::Visible;
        break;
    case false:
        currentVisibilty = ESlateVisibility::Hidden;
        break;
    }

    TeamInCheck->SetText(FText::FromString(name));
    CheckTextVBox->SetVisibility(currentVisibilty);
}

void UCh_OnScreenWidget::SetCheckmatePanel(FString name)
{
    CheckmateTeam->SetText(FText::FromString(name));
    CheckmatePanel->SetVisibility(ESlateVisibility::Visible);
}

