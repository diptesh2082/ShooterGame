// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "TheShooter.h"
#include "AIController.h"
UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (!OwnerComp.GetAIOwner())
    {
        return EBTNodeResult::Failed;
    }

    ATheShooter* Shooter  = Cast<ATheShooter>(OwnerComp.GetAIOwner()->GetPawn());
    if (!Shooter)
    {
        return EBTNodeResult::Failed;
    }
    
    Shooter->Shoot();
    return EBTNodeResult::Succeeded;
}
