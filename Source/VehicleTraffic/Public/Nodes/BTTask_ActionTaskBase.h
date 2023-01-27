// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ActionTaskBase.generated.h"

/**
 * Should be similar to -> UBTTask_BlueprintBase
 */
UCLASS()
class VEHICLETRAFFIC_API UBTTask_ActionTaskBase : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UBTTask_ActionTaskBase(const FObjectInitializer& ObjectInitializer);

	virtual void Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {}

	virtual void Tick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {}
	
	virtual void Stop() { }

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void EndTask(bool Success = true);

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	EBTNodeResult::Type State;

};
