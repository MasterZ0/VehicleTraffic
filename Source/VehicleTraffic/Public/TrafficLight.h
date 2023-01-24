// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/SplineComponent.h>
#include "TrafficLight.generated.h"

UENUM(BlueprintType)
enum class ETrafficState : uint8
{
    Red,
    Yellow,
    Green
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VEHICLETRAFFIC_API UTrafficLight : public UActorComponent
{
	GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = "TrafficLight")
        float yellowDuration;

    UPROPERTY(EditDefaultsOnly, Category = "TrafficLight")
        float greenDuration;

private:
    UStaticMeshComponent* red;
    UStaticMeshComponent* yellow;
    UStaticMeshComponent* green;
    UStaticMeshComponent* currentLight;
    ETrafficState State;


public:
    UTrafficLight();

    UFUNCTION(BlueprintCallable, Category = "TrafficLight")
        void Init(UStaticMeshComponent* red, UStaticMeshComponent* yellow, UStaticMeshComponent* green);


    UFUNCTION(BlueprintCallable, Category = "TrafficLight")
        void Open();

private:
    void SwitchLight(UStaticMeshComponent* newLight, ETrafficState state);


public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
