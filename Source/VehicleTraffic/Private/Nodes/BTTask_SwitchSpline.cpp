// Fill out your copyright notice in the Description page of Project Settings.

#include "Nodes/BTTask_SwitchSpline.h"

UBTTask_SwitchSpline::UBTTask_SwitchSpline(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "Switch Path";
}

void UBTTask_SwitchSpline::Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
    AAIController* MyController = OwnerComp.GetAIOwner();

    if (!MyController || !MyBlackboard)
    {
        EndTask(false);
        return;
    }

    // OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation()
    Actor = OwnerComp.GetOwner();
    
    USplineLibrary::GetDistanceAlongSplineAtLocation(Spline, Actor->GetActorLocation(), TravelDistance);

    FVector closestPoint = Spline->GetWorldLocationAtDistanceAlongSpline(TravelDistance);

    // Get the distance of the point, this will be used to create a symmetrical curve
    float distance = (closestPoint - Actor->GetActorLocation()).Size();

    // Randomize path direction
    FRotator randomRotation = FRotator::ZeroRotator;
    if (FMath::RandRange(0, 2) == 0)
    {
        distance *= -1;
        randomRotation = FRotator(0, 180, 0);
    }

    // Calculate the target position and rotation
    FVector targetPosition = Spline->GetWorldLocationAtDistanceAlongSpline(TravelDistance + distance);

    FRotator targetRotation = Spline->GetWorldRotationAtDistanceAlongSpline(TravelDistance + distance);
    targetRotation = FRotator(FQuat(targetRotation) * FQuat(randomRotation));

    // Creates a curve with tangents based on the position and rotation of the startPoint and endPoint
    FVector offsetVector = targetRotation.RotateVector(Offset);

    bezierCurve = new BezierCurve(Actor->GetActorLocation(), Actor->GetActorRotation(), targetPosition + offsetVector, targetRotation, CurveSmooth);
}

void UBTTask_SwitchSpline::Tick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float Delta)
{
    float DeltaSpeed = Speed * Delta;
    FVector oldPosition = Actor->GetActorLocation();

    // Update Travel Distance
    TravelDistance += DeltaSpeed;
    FVector newPosition = bezierCurve->GetPointAtDistance(TravelDistance);
    Actor->SetActorLocation(newPosition);

    // Rotate the agent to look towards the new position
    FVector direction = (newPosition - oldPosition).GetSafeNormal();

    FRotator targetRotation = FRotationMatrix::MakeFromX(direction).Rotator();
    Actor->SetActorRotation(targetRotation);

    //Quaternion targetRotation = Quaternion.LookRotation(direction, agent.up);
    //agent.rotation = Quaternion.Euler(agent.rotation.eulerAngles.x, targetRotation.eulerAngles.y, agent.rotation.eulerAngles.z);

    // Check if the agent has reached the end of the curve
    if (FVector::Distance(newPosition, bezierCurve->endPosition) <= DeltaSpeed) 
    {
        EndTask(true);
    }
}

void UBTTask_SwitchSpline::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    delete bezierCurve;
}