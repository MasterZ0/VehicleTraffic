// Fill out your copyright notice in the Description page of Project Settings.

#include "CarAIController.h"

ACarAIController::ACarAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTree Component"));
}

void ACarAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AVehicleBase* Vehicle = Cast<AVehicleBase>(InPawn);

	if (Vehicle == nullptr || BTC == nullptr || !IsValid(Widget))
		return;

	UUserWidget* WidgetInstance = CreateWidget(GetWorld(), Widget);
	WidgetInstance->AddToViewport();

	BBC->InitializeBlackboard(*BlackboardData);

	// Settings
	BBC->SetValueAsInt("DriftPoints", CarAIData->DriftPoints);
	BBC->SetValueAsVector("OffsetRoad", CarAIData->OffsetRoad);

	// Movement
	BBC->SetValueAsFloat("MoveSpeed", CarAIData->MoveSpeed);
	BBC->SetValueAsFloat("YellowLightSpeedMultiplier", CarAIData->YellowLightSpeedMultiplier);
	BBC->SetValueAsFloat("AccelerationMultiplier", CarAIData->AccelerationMultiplier);
	BBC->SetValueAsFloat("DecelerationMultiplier", CarAIData->DecelerationMultiplier);

	// Fuel
	BBC->SetValueAsFloat("MaxFuel", CarAIData->MaxFuel);
	BBC->SetValueAsFloat("MinFuelConsume", CarAIData->MinFuelConsume);
	BBC->SetValueAsFloat("FuelConsumeMultiplier", CarAIData->FuelConsumeMultiplier);

	// Rotation
	BBC->SetValueAsFloat("RotationSpeed", CarAIData->RotationSpeed);
	BBC->SetValueAsFloat("CurveSmooth", CarAIData->CurveSmooth);

	BTC->StartTree(*BehaviorTreeAsset);
}