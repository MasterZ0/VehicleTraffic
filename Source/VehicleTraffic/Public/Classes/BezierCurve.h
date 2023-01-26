// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"

/**
 * 
 */
class VEHICLETRAFFIC_API BezierCurve
{

public:

    FVector startPosition;
    FVector startTangent;

    FVector endTangent;
    FVector endPosition;

    float length;
    const int Resolution = 20;

	BezierCurve();
	~BezierCurve();
    BezierCurve(FVector startPosition, FRotator startRotation, FVector endPosition, FRotator endRotation, float weight);
	//~BezierCurve();

    FVector GetPointAtDistance(float distance);
    float CalculateCurveLength(int resolution);
    FVector GetTransitionPoint(float transition);
    static FVector CalculateCubicBezierPoint(float t, FVector p0, FVector p1, FVector p2, FVector p3);
};
