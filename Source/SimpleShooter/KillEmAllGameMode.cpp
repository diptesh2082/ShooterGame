// Fill out your copyright notice in the Description page of Project Settings.

#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAiController.h"

void AKillEmAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    // UE_LOG(LogTemp , Warning , TEXT("A pawn was killed"));
    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController)
    {
        EndGame(false);
    }
    for (AShooterAiController *Controller : TActorRange<AShooterAiController>(GetWorld()))
    {
        if (!Controller->IsDead())
        {
            return;
        }
    }
    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool BIsPlayerWinner)
{
    for (AController *Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == BIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
