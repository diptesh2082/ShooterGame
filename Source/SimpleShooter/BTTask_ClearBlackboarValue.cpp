// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboarValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboarValue::UBTTask_ClearBlackboarValue()
{
    NodeName = TEXT("Clear BlackBoard Value");
}

EBTNodeResult::Type UBTTask_ClearBlackboarValue::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}
