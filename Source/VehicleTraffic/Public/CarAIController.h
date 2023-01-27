// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "VehicleBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "Data/CarAIData.h"
#include "CarAIController.generated.h"

UCLASS()
class VEHICLETRAFFIC_API ACarAIController : public AAIController
{
	GENERATED_BODY()


public:
	 UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TSubclassOf<UUserWidget> Widget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UCarAIData* CarAIData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBlackboardData* BlackboardData;

	UPROPERTY(transient)
	class UBlackboardComponent* BBC;
	UPROPERTY(transient)
	class UBehaviorTreeComponent* BTC;

	ACarAIController(const FObjectInitializer& ObjectInitializer);
	virtual void OnPossess(APawn* InPawn) override;
};
