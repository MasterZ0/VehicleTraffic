// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/SplineLibrary.h"

void USplineLibrary::GetDistanceAlongSplineAtLocation(const USplineComponent* spline, const FVector agentPosition, float& travelDistance)
{
	float inputKey = spline->FindInputKeyClosestToWorldLocation(agentPosition);
	travelDistance = spline->GetDistanceAlongSplineAtSplineInputKey(inputKey);
}

void USplineLibrary::GetPathDirection(const USplineComponent* Spline, const FVector ActorLocation, const FRotator ActorRotation,
	float& TravelDistance, bool& Inverse)
{
	GetDistanceAlongSplineAtLocation(Spline, ActorLocation, TravelDistance);

	FRotator OutRotation = Spline->GetRotationAtDistanceAlongSpline(TravelDistance, ESplineCoordinateSpace::World);
	
	float Angle = (ActorRotation - OutRotation).GetNormalized().Yaw;
	Angle = FMath::UnwindDegrees(Angle);
	//float Angle = ActorRotation.GetNormalized() - OutRotation.GetNormalized;
	Inverse = FMath::Abs(Angle) > 90.0f;
}

void USplineLibrary::FollowPath(const USplineComponent* spline, const FVector offset, const float speed, const float distance, const float delta, const bool inverse,
	FVector& outPosition, FRotator& outRotation, float& newDistance)
{
	if (!spline)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "[USplineLibrary::FollowPath] Null Reference");
		return;
	}

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

void USplineLibrary::CreateBezierTransition(const USplineComponent* Spline, FVector CurrentPosition, FRotator CurrentRotation, FVector Offset, float Speed, float CurveSmooth, bool GoRight,
	FBezierCurve& OutBezierCurve)
{
	float SplineTravelDistance = 0.f;
	USplineLibrary::GetDistanceAlongSplineAtLocation(Spline, CurrentPosition, SplineTravelDistance);

	FVector closestPoint = Spline->GetWorldLocationAtDistanceAlongSpline(SplineTravelDistance);

	// Get the distance of the point, this will be used to create a symmetrical curve
	float distance = (closestPoint - CurrentPosition).Size();

	// Randomize path direction
	FRotator randomRotation = FRotator::ZeroRotator;
	if (GoRight)
	{
		distance *= -1;
		randomRotation = FRotator(0, 180, 0);
	}

	// Calculate the target position and rotation
	FVector targetPosition = Spline->GetWorldLocationAtDistanceAlongSpline(SplineTravelDistance + distance);

	FRotator targetRotation = Spline->GetWorldRotationAtDistanceAlongSpline(SplineTravelDistance + distance);
	targetRotation = targetRotation + randomRotation;

	// Creates a curve with tangents based on the position and rotation of the startPoint and endPoint
	FVector offsetVector = targetRotation.RotateVector(Offset);

	OutBezierCurve = FBezierCurve(CurrentPosition, CurrentRotation, targetPosition + offsetVector, targetRotation, CurveSmooth);
}

void USplineLibrary::FollowBezier(FBezierCurve BezierCurve, FVector CurrentPosition, const float Speed, const float TravelDistance, const float DeltaTimeSeconds,
	FVector& OutPosition, FRotator& OutRotation, float& NewDistance)
{
	float DeltaSpeed = Speed * DeltaTimeSeconds;

	// Update Travel Distance
	NewDistance = TravelDistance + DeltaSpeed;
	OutPosition = BezierCurve.GetPointAtDistance(NewDistance);

	// Rotate the agent to look towards the new position
	FVector direction = (OutPosition - CurrentPosition).GetSafeNormal();

	OutRotation = FRotationMatrix::MakeFromX(direction).Rotator();
}


void USplineLibrary::CalculateDrift(USplineComponent* Spline, float TravelDistance, float DeltaSpeed, float MaxAngle, bool InverseSpline, float& DriftDegree)
{	
	if (InverseSpline)
	{
		DeltaSpeed *= -1;
	}

	FRotator currentRotation = Spline->GetWorldRotationAtDistanceAlongSpline(TravelDistance);
	FRotator targetRotation = Spline->GetWorldRotationAtDistanceAlongSpline(TravelDistance + DeltaSpeed);

	float weight = FMath::FindDeltaAngle(currentRotation.Yaw, targetRotation.Yaw);
	weight *= MaxAngle;

	DriftDegree = FMath::Clamp(weight, -MaxAngle, MaxAngle);
}