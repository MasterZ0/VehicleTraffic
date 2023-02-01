// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interfaces/Drift.h"
#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "VehicleBase.generated.h"

UCLASS()
class VEHICLETRAFFIC_API AVehicleBase : public AWheeledVehicle, public IDrift
{
	GENERATED_BODY()

private:
	float FuelConsumeMultiplier;
	float MinFuelConsume;
	float MaxFuel;

	float AcellerationMultiplier;
	float DecelerationMultiplier;

	float CurrentFuel;
	float CurrentSpeed;
	float DesiredSpeed;

public:
	AVehicleBase();

	void SetFuelVariables(float NewFuelConsumeMultiplier, float NewMinFuelConsume, float NewMaxFuel);
	void SetSpeedVariables(float NewAcellerationMultiplier, float NewDecelerationMultiplier);
	void AddFuel(float FuelValue);

	void SetDesiredSpeed(float DesiredSpeed);

	float GetSpeed();

private:
	virtual void Tick(float DeltaTime) override;

	void UpdateSpeed(float DeltaTime);
};
