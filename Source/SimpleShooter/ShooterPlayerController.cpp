// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AShooterPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);

        if(HUD != nullptr)
        {
            HUD->AddToViewport();
        }
}
void AShooterPlayerController::GoToMainMenu()
{
    UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUD->RemoveFromViewport();
    if (bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);

        if(WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget* LooseScreen = CreateWidget(this, LooseScreenClass);

        if(LooseScreen != nullptr)
        {
            LooseScreen->AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &AShooterPlayerController::GoToMainMenu, RestartDelay);

}
