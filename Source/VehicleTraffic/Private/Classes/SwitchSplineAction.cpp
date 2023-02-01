// Fill out your copyright notice in the Description page of Project Settings.

#include "Classes/SwitchSplineAction.h"

void USwitchSplineAction::StartTask()
{
    bool GoRight = FMath::RandRange(0, 2) == 0;

    USplineLibrary::CreateBezierTransition(Spline, Actor->GetActorLocation(), Actor->GetActorRotation(), Offset, Speed, CurveSmooth, GoRight, BezierCurve);

    TravelDistance = 0;
}

void USwitchSplineAction::TickTask(float Delta)
{
    USplineLibrary::FollowBezier(BezierCurve, Actor->GetActorLocation(), Speed, TravelDistance, Delta, ResultLocation, ResultRotation, TravelDistance);

    // Check if the agent has reached the end of the curve
    if (FVector::Distance(ResultLocation, BezierCurve.EndLocation) <= Delta * Speed)
    {
        EndTask(true);
    }
}

void USwitchSplineAction::RunSwitchSpline(USplineComponent* InSpline, AActor* InActor, FVector InOffset, float InSpeed, float InCurveSmooth, ActionState& Branches, FVector& OutLocation, FRotator& OutRotation)
{
    Actor = InActor;
    Spline = InSpline;
    Offset = InOffset;
    Speed = InSpeed;
    CurveSmooth = InCurveSmooth;

    RunTask(Branches);

    OutLocation = ResultLocation;
    OutRotation = ResultRotation;
}
