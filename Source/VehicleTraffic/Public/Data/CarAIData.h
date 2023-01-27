// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CarAIData.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETRAFFIC_API UCarAIData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// Settings
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Settings")
	int DriftPoints;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Settings")
	FVector OffsetRoad;

	// Movement
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Movement")
	float MoveSpeed;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Movement")
	float YellowLightSpeedMultiplier;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Movement")
	float AccelerationMultiplier;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Movement")
	float DecelerationMultiplier;

	// Fuel
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Fuel")
	float MaxFuel;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Fuel")
	float MinFuelConsume;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Fuel")
	float FuelConsumeMultiplier;

	// Rotation
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Rotation")
	float RotationSpeed;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Rotation")
	float CurveSmooth;
};
