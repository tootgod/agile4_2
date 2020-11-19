// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGamemode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
#include "ShooterPlayerController.h"


void AKillEmAllGamemode::PawnKilled(APawn* Pawnkilled)
{
    Super::PawnKilled(Pawnkilled);


    APlayerController* PlayerController = Cast<APlayerController>(Pawnkilled->GetController());    
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

     for(AShooterAIController* AIController: TActorRange<AShooterAIController>(GetWorld()))
     {
         if (!AIController->IsDead())
         {
             return;
         }
     }
     EndGame(true);
}

void AKillEmAllGamemode::EndGame(bool bIsPlayerWinner)
{
    for(AController* Controller: TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}

