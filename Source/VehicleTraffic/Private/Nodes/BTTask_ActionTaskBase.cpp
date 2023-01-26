// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/BTTask_ActionTaskBase.h"

EBTNodeResult::Type UBTTask_ActionTaskBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Call Start at the first time
	if (!this->running)
	{
		EBTNodeResult::Type result = this->Start(OwnerComp, NodeMemory);

		if (result != EBTNodeResult::Type::InProgress)
			return result;

		this->running = true;
	}

	EBTNodeResult::Type result = this->Update(OwnerComp, NodeMemory);

	if (result != EBTNodeResult::Type::InProgress)
	{
		this->running = false;
	}

	return result;
}