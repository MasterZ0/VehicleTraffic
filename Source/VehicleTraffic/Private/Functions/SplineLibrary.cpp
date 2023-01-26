// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/SplineLibrary.h"

void USplineLibrary::GetDistanceAlongSplineAtLocation(const USplineComponent* spline, const FVector agentPosition, float& travelDistance)
{
	float inputKey = spline->FindInputKeyClosestToWorldLocation(agentPosition);
	travelDistance = spline->GetDistanceAlongSplineAtSplineInputKey(inputKey);
}

void USplineLibrary::GetPathDirection(const USplineComponent* spline, const FVector agentPosition, const FRotator agentRotation,
	FRotator& outRotation, float& travelDistance, bool& inverse)
{
	//float inputKey = spline->FindInputKeyClosestToWorldLocation(agentPosition);
	//travelDistance = spline->GetDistanceAlongSplineAtSplineInputKey(inputKey);
	GetDistanceAlongSplineAtLocation(spline, agentPosition, travelDistance);

	outRotation = spline->GetRotationAtDistanceAlongSpline(travelDistance, ESplineCoordinateSpace::World);

	float angle = agentRotation.Yaw - outRotation.Yaw;
	inverse = FMath::Abs(angle) > 90.0f;
}

void USplineLibrary::FollowPath(const USplineComponent* spline, const FVector offset, const float speed, const float distance, const float delta, const bool inverse,
	FVector& outPosition, FRotator& outRotation, float& newDistance)
{

	float splineDistance = spline->GetSplineLength();
	FRotator extraRotator;
	if (inverse) 
	{
		newDistance = distance - speed * delta;
		extraRotator = FRotator(0.f, 180.f, 0.f);
		if (newDistance < 0)
		{
			newDistance += splineDistance;
		}
	}
	else 
	{
		newDistance = distance + speed * delta;
		extraRotator = FRotator(0.f, 0.f, 0.f);
		if (newDistance >= splineDistance)
		{
			newDistance -= splineDistance;
		}
	}

	FRotator newRotator = spline->GetWorldRotationAtDistanceAlongSpline(newDistance) + extraRotator;
	FVector newPosition = spline->GetWorldLocationAtDistanceAlongSpline(newDistance);

	outPosition = newPosition + (FQuat(newRotator) * offset);
	outRotation = newRotator;
}