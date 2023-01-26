// Fill out your copyright notice in the Description page of Project Settings.

#include "Nodes/BTTask_WaitUntilTrigger.h"


UBTTask_WaitUntilTrigger::UBTTask_WaitUntilTrigger(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bCreateNodeInstance = true;
    NodeName = "Wait Until Trigger";
    this->triggered = false;
}

EBTNodeResult::Type UBTTask_WaitUntilTrigger::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (this->triggered)
    {
        this->triggered = false;
        return EBTNodeResult::Type::Succeeded;
    }

    if (!this->registered)
    {
        TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &UBTTask_WaitUntilTrigger::OnOverlapBegin);
        this->registered = true;
    }

    return EBTNodeResult::Type::InProgress;
}

void UBTTask_WaitUntilTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &UBTTask_WaitUntilTrigger::OnOverlapBegin);
    this->registered = false;
    this->triggered = true;
}