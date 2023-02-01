// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"
#include "BezierCurve.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct VEHICLETRAFFIC_API FBezierCurve
{
    GENERATED_BODY()
public:

    FVector StartLocation;
    FVector StartTangent;

    FVector EndTangent;
    FVector EndLocation;

    float Length;
    const int DefaultResolution = 20;

	FBezierCurve();
	~FBezierCurve();
    FBezierCurve(FVector CurrentLocation, FRotator CurrentRotation, FVector TargetLocation, FRotator TargetRotation, float Weight);

    FVector GetPointAtDistance(float Distance);
    float CalculateCurveLength(int Resolution);
    FVector GetTransitionPoint(float Transition);
    static FVector CalculateCubicBezierPoint(float T, FVector P0, FVector P1, FVector P2, FVector P3);

    FBezierCurve& operator=(const FBezierCurve& Other);
};
