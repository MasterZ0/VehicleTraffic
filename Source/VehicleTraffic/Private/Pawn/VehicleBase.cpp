// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/VehicleBase.h"

AVehicleBase::AVehicleBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVehicleBase::SetFuelVariables(float NewFuelConsumeMultiplier, float NewMinFuelConsume, float NewMaxFuel)
{
    FuelConsumeMultiplier = NewFuelConsumeMultiplier;
    MinFuelConsume = NewMinFuelConsume;
    MaxFuel = NewMaxFuel;
}

void AVehicleBase::SetSpeedVariables(float NewAcellerationMultiplier, float NewDecelerationMultiplier)
{
    AcellerationMultiplier = NewAcellerationMultiplier;
    DecelerationMultiplier = NewDecelerationMultiplier;
}

void AVehicleBase::AddFuel(float FuelValue)
{
    CurrentFuel += FuelValue;
    if (CurrentFuel > MaxFuel)
    {
        CurrentFuel = MaxFuel;
    }
}

void AVehicleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    UpdateSpeed(DeltaTime);
}

void AVehicleBase::UpdateSpeed(float DeltaTime)
{
    // Check if has Fuel
    if (CurrentFuel <= 0)
    {
        CurrentSpeed = FMath::FInterpTo(CurrentSpeed, 0.f, DeltaTime, DecelerationMultiplier);
        return;
    }

    float SpeedMultiplier = DesiredSpeed >= CurrentSpeed ? AcellerationMultiplier : DecelerationMultiplier;

    // Update Speed
    CurrentSpeed = FMath::FInterpTo(CurrentSpeed, DesiredSpeed, DeltaTime, SpeedMultiplier);

    // Update Fuel
    CurrentFuel -= FMath::Max(MinFuelConsume, CurrentSpeed * FuelConsumeMultiplier);
}


float AVehicleBase::GetSpeed()
{
    return CurrentSpeed;
}

void AVehicleBase::SetDesiredSpeed(float NewDesiredSpeed)
{
    DesiredSpeed = NewDesiredSpeed;
}