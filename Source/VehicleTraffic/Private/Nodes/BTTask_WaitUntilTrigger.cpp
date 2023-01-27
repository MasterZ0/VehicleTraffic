// Fill out your copyright notice in the Description page of Project Settings.

#include "Nodes/BTTask_WaitUntilTrigger.h"


UBTTask_WaitUntilTrigger::UBTTask_WaitUntilTrigger(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bCreateNodeInstance = true;
    NodeName = "Wait Until Trigger";
}

void UBTTask_WaitUntilTrigger::Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &UBTTask_WaitUntilTrigger::OnOverlapBegin);
}

void UBTTask_WaitUntilTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &UBTTask_WaitUntilTrigger::OnOverlapBegin);
    EndTask(true);
}

void UBTTask_WaitUntilTrigger::Stop() 
{
    TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &UBTTask_WaitUntilTrigger::OnOverlapBegin);
}