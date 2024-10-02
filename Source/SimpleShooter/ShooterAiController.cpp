// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAiController.h"
#include "kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TheShooter.h"
void AShooterAiController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
        APawn *PlayerPawn =  UGameplayStatics::GetPlayerPawn(GetWorld() , 0);

        // SetFocus(PlayerPawn);
        // GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }

}

void AShooterAiController::Tick(float DeltaTime)
{   
    Super::Tick(DeltaTime);
    // APawn *PlayerPawn =  UGameplayStatics::GetPlayerPawn(GetWorld() , 0);
    
    
    // if (LineOfSightTo(PlayerPawn))
    // {
    //     FVector PlayerLocation = PlayerPawn->GetActorLocation();
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerLocation);
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerLocation);
    // }else{
    //     GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    // };

}

bool AShooterAiController::IsDead() const
{
    ATheShooter* ControllerCharacter = Cast<ATheShooter>(GetPawn());
    if(ControllerCharacter)
    {
        return ControllerCharacter->IsDead();
    }
    return true;
}
