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
    float U = 1 - T;
    float UU = U * U;
    float UUU = UU * U;

    float TT = T * T;
    float TTT = TT * T;

    return (UUU * P0) + (3 * UU * T * P1) + (3 * U * TT * P2) + (TTT * P3);
}

float FBezierCurve::CalculateCurveLength(int Resolution)
{
    float TransitionSize = 1.f / Resolution;
    float CurveLength = 0;
    FVector PreviousPosition = StartLocation;

    for (size_t i = 1; i <= Resolution; i++)
    {
        float t = i * TransitionSize;
        FVector NewPoint = CalculateCubicBezierPoint(t, StartLocation, StartTangent, EndTangent, EndLocation);
        CurveLength += FVector::Distance(PreviousPosition, NewPoint);
        PreviousPosition = NewPoint;
    }

    return CurveLength;
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