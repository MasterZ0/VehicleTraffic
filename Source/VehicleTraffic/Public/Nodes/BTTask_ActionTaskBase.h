// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ActionTaskBase.generated.h"

/**
 * Should be similar to -> UBTTask_BlueprintBase
 */
UCLASS()
class VEHICLETRAFFIC_API UBTTask_ActionTaskBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
	{
		return EBTNodeResult::Type::InProgress;
	}

	virtual EBTNodeResult::Type Update(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
	{
		return EBTNodeResult::Type::InProgress;
	}

	/*UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree")
		virtual void FinishExecute(bool Success = true);

	UFUNCTION(BlueprintImplementableEvent, Category = AI)
		virtual void ReceiveExecuteAI(AAIController* OwnerController, AActor* ControlledPawn);

	UFUNCTION(BlueprintImplementableEvent)
		virtual void ReceiveTick(AActor* OwnerActor, float DeltaSeconds);

	UFUNCTION(BlueprintImplementableEvent, Category = AI)
		virtual void ReceiveTickAI(AAIController* OwnerController, AActor* ControlledPawn, float DeltaSeconds);

	UFUNCTION(BlueprintImplementableEvent)
		virtual void ReceiveExecute(AActor* OwnerActor);*/
	
	virtual void Stop() { }

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	bool running;

};
