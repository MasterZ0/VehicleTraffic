// Fill out your copyright notice in the Description page of Project Settings.

#include "Nodes/BTTask_WaitUntilTrigger.h"


UBTTask_WaitUntilTrigger::UBTTask_WaitUntilTrigger(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bCreateNodeInstance = true;
    NodeName = "Wait Until Trigger";
}

void UBTTask_WaitUntilTrigger::Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UObject* obj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(ComponentToOverlap.SelectedKeyName);
    PrimitiveComponent = Cast<UPrimitiveComponent>(obj);

    if (!PrimitiveComponent)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "[UBTTask_WaitUntilTrigger::Start] Null Reference");
        EndTask(false);
        return;
    }

    this->LocalOwnerComp = &OwnerComp;
    PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UBTTask_WaitUntilTrigger::OnOverlapBegin);
}

void UBTTask_WaitUntilTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA(ClassType))
    {
        LocalOwnerComp->GetBlackboardComponent()->SetValueAsObject(ReturnValue.SelectedKeyName, OtherActor);
    }
    else if (OtherComp->IsA(ClassType))
    {
        LocalOwnerComp->GetBlackboardComponent()->SetValueAsObject(ReturnValue.SelectedKeyName, OtherComp);
    }
    else
    {
        UActorComponent* component = OtherActor->GetComponentByClass(ClassType);
        if (IsValid(component))
        {
            LocalOwnerComp->GetBlackboardComponent()->SetValueAsObject(ReturnValue.SelectedKeyName, component);
        }
        else
        {
            return;
        }

    }

    PrimitiveComponent->OnComponentBeginOverlap.RemoveDynamic(this, &UBTTask_WaitUntilTrigger::OnOverlapBegin);
    EndTask(true);
}

void UBTTask_WaitUntilTrigger::Stop() 
{
    if (!PrimitiveComponent)
        return;

    PrimitiveComponent->OnComponentBeginOverlap.RemoveDynamic(this, &UBTTask_WaitUntilTrigger::OnOverlapBegin);
}