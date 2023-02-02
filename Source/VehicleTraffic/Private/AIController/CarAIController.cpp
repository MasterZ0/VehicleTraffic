// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController/CarAIController.h"

ACarAIController::ACarAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void ACarAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Vehicle = Cast<AVehicleBase>(InPawn);

	if (Vehicle == nullptr)
		return;

	// Instantia Tasks
	FollowSplineAction = NewObject<UFollowSplineAction>(this);
	SwitchSplineAction = NewObject<USwitchSplineAction>(this);

	// Set Fuel and Acceleration variables
	Vehicle->SetSpeedVariables(CarAIData->AccelerationMultiplier, CarAIData->DecelerationMultiplier);
	Vehicle->SetFuelVariables(CarAIData->FuelConsumeMultiplier, CarAIData->MinFuelConsume, CarAIData->MaxFuel);
	Vehicle->AddFuel(CarAIData->StartFuel);

	// Attach to Vehicle and update position 
	this->AttachToActor(Vehicle, FAttachmentTransformRules::KeepRelativeTransform);
	this->SetInitialLocationAndRotation(Vehicle->GetActorLocation(), Vehicle->GetActorRotation());

	// Get Dependencies
	CarTriggerDetection = Cast<UCarTriggerDetection>(Vehicle->GetComponentByClass(UCarTriggerDetection::StaticClass()));

}

void ACarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentSpline || GetWorld()->IsPaused())
		return;

	// Update Speed
	UpdateDesiredSpeed();
	float Speed = Vehicle->GetSpeed();

	MoveVehicle(Speed, DeltaTime);
}

void ACarAIController::MoveVehicle(float Speed, float DeltaTime)
{
	FVector OutLocation;
	FRotator OutRotation;
	if (!SwitchSpline)
	{
		ActionState Branches;
		float TravelDistance;
		bool InverseSpline;
		FollowSplineAction->RunFollowSpline(CurrentSpline, Vehicle, CarAIData->OffsetRoad, Speed, Branches, OutLocation, OutRotation, TravelDistance, InverseSpline);

		// Calculate Drift
		CalculateDriftAngle(Speed, DeltaTime, TravelDistance, InverseSpline);
		OutRotation += FRotator(0, CurrentDriftDegree, 0);
	}
	else // Switch Spline
	{
		ActionState Branches;
		SwitchSplineAction->RunSwitchSpline(CurrentSpline, Vehicle, CarAIData->OffsetRoad, Speed, CarAIData->CurveSmooth, Branches, OutLocation, OutRotation);

		if (Branches == ActionState::Success)
		{
			NextSwitchSpline = GetWorld()->GetTimeSeconds() + CarAIData->DelayToSwitchSpline;
			SwitchSplineAction->Reset();
			FollowSplineAction->Reset();
			SwitchSpline = false;
		}
	}

	// Set Position
	Vehicle->SetActorLocationAndRotation(OutLocation, OutRotation, false, nullptr, ETeleportType::TeleportPhysics);
}

void ACarAIController::CalculateDriftAngle(float Speed, float DeltaTime, float TravelDistance, bool InverseSpline)
{
	float DriftDegree = 0.f;
	if (DriftZone)
	{
		USplineLibrary::CalculateDrift(CurrentSpline, TravelDistance, Speed * DeltaTime, CarAIData->MaxDriftRotation, InverseSpline, DriftDegree);
	}
	CurrentDriftDegree = FMath::FInterpTo(CurrentDriftDegree, DriftDegree, DeltaTime, CarAIData->RotationSpeed);
}

void ACarAIController::UpdateDesiredSpeed()
{
	float Speed = CarAIData->MoveSpeed;
	bool HasObstacle = false;

	// Traffic Light logic
	UTrafficLight* TrafficLight = CarTriggerDetection->GetTrafficLight();
	if (TrafficLight)
	{
		ETrafficState TrafficState = TrafficLight->GetTrafficState();
		if (CarState == ECarState::YellowState || TrafficState == ETrafficState::Yellow)
		{
			CarState = ECarState::YellowState;
			Speed *= CarAIData->YellowLightSpeedMultiplier;
		}
		else if (TrafficState == ETrafficState::Red)
		{
			HasObstacle = true;
		}
	}
	else
	{
		CarState = ECarState::Standard;
	}

	// Check for obstacle
	if (CarTriggerDetection->HasObstacle())
	{
		HasObstacle = true;
	}

	// Obstacle logic
	if (HasObstacle)
	{
		Speed = 0.f;
	}

	Vehicle->SetDesiredSpeed(Speed);
}

void ACarAIController::OnOverlapBeginRoadDetector(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if can Switch Spline
	float Time = GetWorld()->GetTimeSeconds();
	if (NextSwitchSpline - Time > 0.f || SwitchSpline || !CurrentSpline)
		return;

	// Random chance to Switch Spline
	bool Switch = FMath::RandRange(0, 100) < CarAIData->ChanceToSwitchSpline;
	if (!Switch)
		return;

	// Get Component and check if is valid, and then update the Spline
	USplineComponent* Component = Cast<USplineComponent>(OtherActor->GetComponentByClass(USplineComponent::StaticClass()));
	if (IsValid(Component) && Component != CurrentSpline)
	{
		CurrentSpline = Component; 
		SwitchSpline = true;
	}
}

void ACarAIController::OnEnterDriftZone() 
{
	DriftZone = true;
	Vehicle->AddPoints(CarAIData->DriftPoints);
}
void ACarAIController::OnExitDriftZone() 
{
	DriftZone = false;
}