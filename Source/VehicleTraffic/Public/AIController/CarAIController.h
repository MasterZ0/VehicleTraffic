// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Data/CarAIData.h"
#include "Interfaces/Drift.h"
#include "Classes/FollowSplineAction.h"
#include "Classes/SwitchSplineAction.h"
#include "Components/CarTriggerDetection.h"
#include "Components/TrafficLight.h"
#include "Pawn/VehicleBase.h"

#include "Components/SplineComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "CarAIController.generated.h"

UENUM()
enum class ECarState: uint8
{
	/*  */
	Standard,
	/*  */
	YellowState,
};

UCLASS()
class VEHICLETRAFFIC_API ACarAIController : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UCarAIData* CarAIData;

	UPROPERTY(BlueprintReadOnly, Instanced)
	UFollowSplineAction* FollowSplineAction;

	UPROPERTY(BlueprintReadOnly, Instanced)
	USwitchSplineAction* SwitchSplineAction;

	UPROPERTY(BlueprintReadWrite)
	USplineComponent* CurrentSpline;

private:

	AVehicleBase* Vehicle;
	UCarTriggerDetection* CarTriggerDetection;
	ECarState CarState;

	// Drift
	float CurrentDriftDegree;
	bool DriftZone;

	// Path Control
	float NextSwitchSpline;
	bool SwitchSpline;

public:
	ACarAIController(const FObjectInitializer& ObjectInitializer);
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Interfaces")
	void OnEnterDriftZone();

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Interfaces")
	void OnExitDriftZone();

	UFUNCTION(BlueprintCallable, Category = "Test")
	void OnOverlapBeginRoadDetector(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void UpdateDesiredSpeed();

	void Tick(float DeltaTime) override;
	void MoveVehicle(float Speed, float DeltaTime);
	void CalculateDriftAngle(float Speed, float DeltaTime, float TravelDistance, bool InverseSpline);
};
