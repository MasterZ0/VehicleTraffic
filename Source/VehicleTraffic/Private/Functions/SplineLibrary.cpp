// Fill out your copyright notice in the Description page of Project Settings.

#include "Functions/SplineLibrary.h"

void USplineLibrary::GetClosestDistanceToLocation(const USplineComponent* Spline, const FVector ActorLocation, float& TravelDistance)
{
	float InputKey = Spline->FindInputKeyClosestToWorldLocation(ActorLocation);
	TravelDistance = Spline->GetDistanceAlongSplineAtSplineInputKey(InputKey);
}

void USplineLibrary::GetSplineDirection(const USplineComponent* Spline, const FVector ActorLocation, const FRotator ActorRotation,
	float& TravelDistance, bool& Inverse)
{
	GetClosestDistanceToLocation(Spline, ActorLocation, TravelDistance);

	FRotator OutRotation = Spline->GetRotationAtDistanceAlongSpline(TravelDistance, ESplineCoordinateSpace::World);
	
	float Angle = (ActorRotation - OutRotation).GetNormalized().Yaw;
	Angle = FMath::UnwindDegrees(Angle);

	Inverse = FMath::Abs(Angle) > 90.0f;
}

void USplineLibrary::FollowSpline(const USplineComponent* Spline, const FVector Offset, const float Speed, const float TravelDistance, const float DeltaTime, const bool InverseSpline,
	FVector& OutLocation, FRotator& OutRotation, float& OutTravelDistance)
{
	if (!Spline)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "[USplineLibrary::FollowPath] Null Reference");
		return;
	}

	float SplineDistance = Spline->GetSplineLength();
	FRotator ExtraRotator;
	if (InverseSpline)
	{
		OutTravelDistance = TravelDistance - Speed * DeltaTime;
		ExtraRotator = FRotator(0.f, 180.f, 0.f);
		if (OutTravelDistance < 0)
		{
			OutTravelDistance += SplineDistance;
		}
	}
	else 
	{
		OutTravelDistance = TravelDistance + Speed * DeltaTime;
		ExtraRotator = FRotator(0.f, 0.f, 0.f);
		if (OutTravelDistance >= SplineDistance)
		{
			OutTravelDistance -= SplineDistance;
		}
	}

	FRotator NewRotator = Spline->GetWorldRotationAtDistanceAlongSpline(OutTravelDistance) + ExtraRotator;
	FVector NewLocation = Spline->GetWorldLocationAtDistanceAlongSpline(OutTravelDistance);

	OutLocation = NewLocation + (FQuat(NewRotator) * Offset);
	OutRotation = NewRotator;
}

void USplineLibrary::CreateBezierTransition(const USplineComponent* Spline, FVector ActorLocation, FRotator ActorRotation, FVector Offset, float Speed, float CurveSmooth, bool GoRight,
	FBezierCurve& OutBezierCurve)
{
	float SplineTravelDistance = 0.f;
	USplineLibrary::GetClosestDistanceToLocation(Spline, ActorLocation, SplineTravelDistance);

	FVector closestPoint = Spline->GetWorldLocationAtDistanceAlongSpline(SplineTravelDistance);

	// Get the distance of the point, this will be used to create a symmetrical curve
	float TravelDistance = (closestPoint - ActorLocation).Size();

	// Randomize path direction
	FRotator ExtraRotation = FRotator::ZeroRotator;
	if (GoRight)
	{
		TravelDistance *= -1;
		ExtraRotation = FRotator(0, 180, 0);
	}

	// Calculate the target position and rotation
	FVector TargetLocation = Spline->GetWorldLocationAtDistanceAlongSpline(SplineTravelDistance + TravelDistance);

	FRotator TargetRotation = Spline->GetWorldRotationAtDistanceAlongSpline(SplineTravelDistance + TravelDistance);
	TargetRotation = TargetRotation + ExtraRotation;

	// Creates a curve with tangents based on the position and rotation of the startPoint and endPoint
	FVector OffsetVector = TargetRotation.RotateVector(Offset);

	OutBezierCurve = FBezierCurve(ActorLocation, ActorRotation, TargetLocation + OffsetVector, TargetRotation, CurveSmooth);
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

	FRotator CurrentRotation = Spline->GetWorldRotationAtDistanceAlongSpline(TravelDistance);
	FRotator TargetRotation = Spline->GetWorldRotationAtDistanceAlongSpline(TravelDistance + DeltaSpeed);

	float Weight = FMath::FindDeltaAngle(CurrentRotation.Yaw, TargetRotation.Yaw);
	Weight *= MaxAngle;

	DriftDegree = FMath::Clamp(Weight, -MaxAngle, MaxAngle);
}