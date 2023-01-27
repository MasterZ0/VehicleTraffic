// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/SplineComponent.h"
#include "SplineLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETRAFFIC_API USplineLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "_Vehicle Traffic\Spline Library")
	static void GetDistanceAlongSplineAtLocation(const USplineComponent* spline, const FVector agentPosition, float& travelDistance);

	UFUNCTION(BlueprintCallable, Category = "_Vehicle Traffic\Spline Library")
	static void FollowPath(const USplineComponent* spline, const FVector offset, const float speed, const float distance, const float delta, const bool inverse,
		FVector& outPosition, FRotator& outRotation, float& newDistance);

	UFUNCTION(BlueprintCallable, Category = "_Vehicle Traffic\Spline Library")
	static void GetPathDirection(const USplineComponent* spline, const FVector agentPosition, const FRotator agentRotation, 
		float& travelDistance, bool& inverse);
};