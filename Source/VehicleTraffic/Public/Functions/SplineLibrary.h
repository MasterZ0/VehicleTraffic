// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Classes/BezierCurve.h"
#include "Templates/Invoke.h"
#include "Delegates/Delegate.h"

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

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Spline Library")
	static void GetDistanceAlongSplineAtLocation(const USplineComponent* spline, const FVector agentPosition, float& travelDistance);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Spline Library")
	static void FollowPath(const USplineComponent* spline, const FVector offset, const float speed, const float distance, const float delta, const bool inverse,
		FVector& outPosition, FRotator& outRotation, float& newDistance);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Spline Library")
	static void GetPathDirection(const USplineComponent* spline, const FVector agentPosition, const FRotator agentRotation, 
		float& travelDistance, bool& inverse);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Spline Library")
	static void  CreateBezierTransition(const USplineComponent* Spline, FVector CurrentPosition, FRotator CurrentRotation, FVector Offset, float Speed, float CurveSmooth, bool GoRight,
		FBezierCurve& OutBezierCurve);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Spline Library")
	static void FollowBezier(FBezierCurve BezierCurve, FVector CurrentPosition, const float Speed, const float TravelDistance, const float DeltaTimeSeconds,
		FVector& OutPosition, FRotator& OutRotation, float& NewDistance);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Spline Library")
		static void CalculateDrift(USplineComponent* Spline, float TravelDistance, float DeltaSpeed, float MaxAngle, bool InverseSpline,
			float& DriftDegree);
};