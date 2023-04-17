// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/VehicleBase.h"

AVehicleBase::AVehicleBase()
{
	PrimaryActorTick.bCanEverTick = true;

    LeftWheelParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LeftWheelParticles"));
    LeftWheelParticles->SetupAttachment(RootComponent);
    LeftWheelParticles->SetAutoActivate(false);

    RightWheelParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RightWheelParticles"));
    RightWheelParticles->SetupAttachment(RootComponent);
    RightWheelParticles->SetAutoActivate(false);

    DriftZoneDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("DriftZoneDetector"));
    DriftZoneDetector->SetupAttachment(RootComponent);
    DriftZoneDetector->bEditableWhenInherited = true;
    RoadDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("RoadDetector"));
    RoadDetector->SetupAttachment(RootComponent);

    //CarTriggerDetection = CreateDefaultSubobject<UCarTriggerDetection>(TEXT("CarTriggerDetection"));
    //CarTriggerDetection->SetupAttachment(RootComponent);
}

void AVehicleBase::BeginPlay()
{
    if (!IsValid(Widget))
        return;

    // Widget
    WidgetInstance = CreateWidget(GetWorld(), Widget);
    WidgetInstance->AddToViewport();

    Super::BeginPlay();
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
    CurrentFuel -= FMath::Max(MinFuelConsume, CurrentSpeed / 100.f) * FuelConsumeMultiplier;
    CurrentFuel = FMath::Max(0.f, CurrentFuel);
}

void AVehicleBase::SetDesiredSpeed(float NewDesiredSpeed)
{
    DesiredSpeed = NewDesiredSpeed;
}

float AVehicleBase::GetFuelPercentage()
{
    return CurrentFuel / MaxFuel;
}

float AVehicleBase::GetSpeed()
{
    return CurrentSpeed;
}

int AVehicleBase::GetScore()
{
    return Score;
}

void AVehicleBase::AddPoints(int PointValue)
{
    Score += PointValue;
}