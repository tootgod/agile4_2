// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        APawn* ControllerPawn = GetPawn();

        if (ControllerPawn != nullptr)
        {
          GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), ControllerPawn ->GetActorLocation());
        }

        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn ->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(LineOfSightTo(PlayerPawn))
    {
      GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn ->GetActorLocation());
      GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn ->GetActorLocation());
    }
    else
    {
      GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }
}