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
	static void GetClosestDistanceToLocation(const USplineComponent* Spline, const FVector ActorLocation, float& TravelDistance);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Spline Library")
	static void GetSplineDirection(const USplineComponent* Spline, const FVector ActorLocation, const FRotator ActorRotation,
		float& TravelDistance, bool& InverseSpline);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Spline Library")
	static void FollowSpline(const USplineComponent* Spline, const FVector Offset, const float Speed, const float TravelDistance, const float DeltaTime, const bool InverseSpline,
		FVector& OutLocation, FRotator& OutRotation, float& OutTravelDistance);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Spline Library")
	static void  CreateBezierTransition(const USplineComponent* Spline, FVector ActorLocation, FRotator ActorRotation, FVector Offset, float Speed, float CurveSmooth, bool GoRight,
		FBezierCurve& OutBezierCurve);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Spline Library")
	static void FollowBezier(FBezierCurve BezierCurve, FVector CurrentPosition, const float Speed, const float TravelDistance, const float DeltaTimeSeconds,
		FVector& OutPosition, FRotator& OutRotation, float& NewDistance);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Spline Library")
		static void CalculateDrift(USplineComponent* Spline, float TravelDistance, float DeltaSpeed, float MaxAngle, bool InverseSpline,
			float& DriftDegree);
};