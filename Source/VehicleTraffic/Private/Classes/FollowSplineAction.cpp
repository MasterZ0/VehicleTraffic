// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/FollowSplineAction.h"

void UFollowSplineAction::StartTask()
{
	USplineLibrary::GetPathDirection(Spline, Actor->GetActorLocation(), Actor->GetActorRotation(), TravelDistance, InverseSpline);
}

void UFollowSplineAction::TickTask(float Delta)
{
	USplineLibrary::FollowPath(Spline, Offset, Speed, TravelDistance, Delta, InverseSpline, ResultLocation, ResultRotation, TravelDistance);
}

void UFollowSplineAction::RunFollowSpline(USplineComponent* InSpline, AActor* InActor, FVector InOffset, float InSpeed, ActionState& Branches, FVector& OutLocation, FRotator& OutRotation, float& OutTravelDistance, bool& OutInverseSpline)
{
	Actor = InActor;
	Spline = InSpline;
	Offset = InOffset;
	Speed = InSpeed;

	RunTask(Branches);

	OutLocation = ResultLocation;
	OutRotation = ResultRotation;
	OutTravelDistance = TravelDistance;
	OutInverseSpline = InverseSpline;
}