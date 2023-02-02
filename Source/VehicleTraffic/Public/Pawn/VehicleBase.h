// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "VehicleBase.generated.h"

UCLASS()
class VEHICLETRAFFIC_API AVehicleBase : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<UUserWidget> Widget;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	UUserWidget* WidgetInstance;

private:
	float FuelConsumeMultiplier;
	float MinFuelConsume;
	float MaxFuel;
	float CurrentFuel;

	float AcellerationMultiplier;
	float DecelerationMultiplier;

	float CurrentSpeed;
	float DesiredSpeed;

	int Score;

public:
	AVehicleBase();

	UFUNCTION(BlueprintCallable, Category = "Vehicle Base")
	float GetFuelPercentage();
	UFUNCTION(BlueprintCallable, Category = "Vehicle Base")
	float GetSpeed();
	UFUNCTION(BlueprintCallable, Category = "Vehicle Base")
	int GetScore();

	void AddPoints(int PointValue);

	void SetFuelVariables(float NewFuelConsumeMultiplier, float NewMinFuelConsume, float NewMaxFuel);
	void SetSpeedVariables(float NewAcellerationMultiplier, float NewDecelerationMultiplier);
	void AddFuel(float FuelValue);

	void SetDesiredSpeed(float DesiredSpeed);

private:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void UpdateSpeed(float DeltaTime);
};
