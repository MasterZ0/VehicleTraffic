// Fill out your copyright notice in the Description page of Project Settings.

#include "Nodes/BTTask_SwitchSpline.h"

UBTTask_SwitchSpline::UBTTask_SwitchSpline(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "Switch Spline";
}

void UBTTask_SwitchSpline::Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    Actor = OwnerComp.GetAIOwner()->GetPawn();

    if (!Actor || !Blackboard)
    {
        EndTask(false);
        return;
    }

    Spline = Cast<USplineComponent>(Blackboard->GetValueAsObject(SplineKey.SelectedKeyName));
    Offset = Blackboard->GetValueAsVector(OffsetKey.SelectedKeyName);
    Speed = Blackboard->GetValueAsFloat(SpeedKey.SelectedKeyName);
    CurveSmooth = Blackboard->GetValueAsFloat(CurveSmoothKey.SelectedKeyName);

    TravelDistance = 0;

    bool GoRight = FMath::RandRange(0, 2) == 0;

    USplineLibrary::CreateBezierTransition(Spline, Actor->GetActorLocation(), Actor->GetActorRotation(), Offset, Speed, CurveSmooth, GoRight, BezierCurve);
}

void UBTTask_SwitchSpline::Tick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float Delta)
{
    FVector NewPosition;
    FRotator NewRotation;

    USplineLibrary::FollowBezier(BezierCurve, Actor->GetActorLocation(), Speed, TravelDistance, Delta, NewPosition, NewRotation, TravelDistance);

    this->Actor->SetActorLocationAndRotation(NewPosition, NewRotation, false, 0, ETeleportType::TeleportPhysics);

    // Check if the agent has reached the end of the curve
    if (FVector::Distance(NewPosition, BezierCurve.EndLocation) <= Delta * Speed)
    {
        EndTask(true);
    }
}