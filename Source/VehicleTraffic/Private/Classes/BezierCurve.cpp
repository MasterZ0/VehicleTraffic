// Fill out your copyright notice in the Description page of Project Settings.

#include "Classes/BezierCurve.h"

BezierCurve::BezierCurve() { }

BezierCurve::BezierCurve(FVector startPosition, FRotator startRotation, FVector endPosition, FRotator endRotation, float weight)
{
    this->startPosition = startPosition;
    this->endPosition = endPosition;

    float distanceMultiplier = (startPosition - endPosition).Size() / 2.f;

    startTangent = startPosition + (startRotation.RotateVector(FVector::ForwardVector) * distanceMultiplier * weight);
    endTangent = endPosition + (endRotation.RotateVector(FVector::BackwardVector) * distanceMultiplier * weight);

    length = CalculateCurveLength(Resolution);
}

BezierCurve::~BezierCurve() { }

FVector BezierCurve::GetPointAtDistance(float distance)
{
    float t = distance / length;
    return GetTransitionPoint(t);
}

FVector BezierCurve::GetTransitionPoint(float transition)
{
    return CalculateCubicBezierPoint(transition, startPosition, startTangent, endTangent, endPosition);
}

FVector BezierCurve::CalculateCubicBezierPoint(float t, FVector p0, FVector p1, FVector p2, FVector p3)
{
    float u = 1 - t;
    float uu = u * u;
    float uuu = uu * u;

    float tt = t * t;
    float ttt = tt * t;

    return (uuu * p0) + (3 * uu * t * p1) + (3 * u * tt * p2) + (ttt * p3);
}

float BezierCurve::CalculateCurveLength(int resolution)
{
    float transitionSize = 1.f / resolution;
    float curveLength = 0;
    FVector previousPosition = startPosition;

    for (int i = 1; i <= resolution; i++)
    {
        float t = i * transitionSize;
        FVector newPosition = CalculateCubicBezierPoint(t, startPosition, startTangent, endTangent, endPosition);
        curveLength += FVector::Distance(previousPosition, newPosition);
        previousPosition = newPosition;
    }

    return curveLength;
}