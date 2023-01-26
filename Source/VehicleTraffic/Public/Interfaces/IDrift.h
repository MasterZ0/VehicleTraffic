// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDrift.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIDrift : public UInterface
{
	GENERATED_BODY()


};

/**
 * 
 */
class VEHICLETRAFFIC_API IIDrift
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle Traffic\Interfaces")
		void OnEnterDriftArea();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Vehicle Traffic\Interfaces")
		void OnExitDriftArea();

};