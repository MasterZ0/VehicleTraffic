// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrafficLight.h"
#include "TrafficController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VEHICLETRAFFIC_API UTrafficController : public UActorComponent
{
	GENERATED_BODY()

public:	
    TArray<UTrafficLight*> Traffics;

	UTrafficController();

	UFUNCTION(BlueprintCallable, Category = "Traffic Controller")
	void Init(TArray<UTrafficLight*> traffics);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
