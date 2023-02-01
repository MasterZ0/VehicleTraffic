// Fill out your copyright notice in the Description page of Project Settings.

#include "Classes/BezierCurve.h"

FBezierCurve::FBezierCurve() { }

FBezierCurve::FBezierCurve(FVector CurrentLocation, FRotator CurrentRotation, FVector TargetLocation, FRotator TargetRotation, float Weight)
{
    StartLocation = CurrentLocation;
    EndLocation = TargetLocation;

    float DistanceMultiplier = (CurrentLocation - TargetLocation).Size() / 2.f;

    StartTangent = CurrentLocation + (CurrentRotation.RotateVector(FVector::ForwardVector) * DistanceMultiplier * Weight);
    EndTangent = TargetLocation + (TargetRotation.RotateVector(FVector::BackwardVector) * DistanceMultiplier * Weight);

    Length = CalculateCurveLength(DefaultResolution);
}

FBezierCurve::~FBezierCurve() { }

FVector FBezierCurve::GetPointAtDistance(float Distance)
{
    float T = Distance / Length;
    return GetTransitionPoint(T);
}

FVector FBezierCurve::GetTransitionPoint(float Transition)
{
    return CalculateCubicBezierPoint(Transition, StartLocation, StartTangent, EndTangent, EndLocation);
}

FVector FBezierCurve::CalculateCubicBezierPoint(float T, FVector P0, FVector P1, FVector P2, FVector P3)
{
    float u = 1 - T;
    float uu = u * u;
    float uuu = uu * u;

    float tt = T * T;
    float ttt = tt * T;

    return (uuu * P0) + (3 * uu * T * P1) + (3 * u * tt * P2) + (ttt * P3);
}

float FBezierCurve::CalculateCurveLength(int Resolution)
{
    float transitionSize = 1.f / Resolution;
    float curveLength = 0;
    FVector previousPosition = StartLocation;

    for (int i = 1; i <= Resolution; i++)
    {
        float t = i * transitionSize;
        FVector newPosition = CalculateCubicBezierPoint(t, StartLocation, StartTangent, EndTangent, EndLocation);
        curveLength += FVector::Distance(previousPosition, newPosition);
        previousPosition = newPosition;
    }

    return curveLength;
}

FBezierCurve& FBezierCurve::operator=(const FBezierCurve& Other)
{
    this->StartLocation = Other.StartLocation;
    this->StartTangent = Other.StartTangent;
    this->EndTangent = Other.EndTangent;
    this->EndLocation = Other.EndLocation;
    this->Length = Other.Length;

    return *this;
}