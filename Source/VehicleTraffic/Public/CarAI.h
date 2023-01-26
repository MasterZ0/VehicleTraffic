// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "CarAI.generated.h"

UCLASS()
class VEHICLETRAFFIC_API ACarAI : public AAIController
{
	GENERATED_BODY()

public:

	ACarAI(const FObjectInitializer& ObjectInitializer);
		virtual void OnPossess(APawn* InPawn) override;


	UPROPERTY(transient)
		class UBlackboardComponent* BBC;
	UPROPERTY(transient)
		class UBehaviorTreeComponent* BTC;

};
