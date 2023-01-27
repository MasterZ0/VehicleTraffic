// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/BTTask_ActionTaskBase.h"

UBTTask_ActionTaskBase::UBTTask_ActionTaskBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_ActionTaskBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	State = EBTNodeResult::Type::InProgress;

	Start(OwnerComp, NodeMemory);

	if (State != EBTNodeResult::Type::InProgress)
	{
		Stop();
	}

	return State;
}

void UBTTask_ActionTaskBase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Tick(OwnerComp, NodeMemory, DeltaSeconds);

	if (State != EBTNodeResult::Type::InProgress) 
	{
		Stop();
		UBTTaskNode* TemplateNode = (UBTTaskNode*)OwnerComp.FindTemplateNode(this);
		OwnerComp.OnTaskFinished(TemplateNode, State);
	}
}

void UBTTask_ActionTaskBase::EndTask(bool Success)
{
	State = Success ? EBTNodeResult::Type::Succeeded : EBTNodeResult::Type::Failed;
}