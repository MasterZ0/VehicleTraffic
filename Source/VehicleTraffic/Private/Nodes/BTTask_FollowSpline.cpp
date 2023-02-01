// Fill out your copyright notice in the Description page of Project Settings.

#include "Nodes/BTTask_FollowSpline.h"

UBTTask_FollowSpline::UBTTask_FollowSpline(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "Follow Spline";
}

void UBTTask_FollowSpline::Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	Actor = OwnerComp.GetAIOwner()->GetPawn();

	if (!Actor || !Blackboard)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "[UBTTask_FollowSpline::Start] Null Reference");
		EndTask(false);
		return;
	}

	Spline = Cast<USplineComponent>(Blackboard->GetValueAsObject(SplineKey.SelectedKeyName));
	Offset = Blackboard->GetValueAsVector(OffsetKey.SelectedKeyName);
	Speed = Blackboard->GetValueAsFloat(SpeedKey.SelectedKeyName);

	if (!Spline) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "[UBTTask_FollowSpline::Start] Null Reference");
		EndTask(false);
		return;
	}

	USplineLibrary::GetPathDirection(Spline, Actor->GetActorLocation(), Actor->GetActorRotation(), TravelDistance, Inverse);

	Blackboard->SetValueAsBool(InverseKey.SelectedKeyName, Inverse);
}

void UBTTask_FollowSpline::Tick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float Delta)
{
	FVector OutLocation = FVector();
	FRotator OutRotation = FRotator();

	USplineLibrary::FollowPath(Spline, Offset, Speed, TravelDistance, Delta, Inverse, OutLocation, OutRotation, TravelDistance);

	this->Actor->SetActorLocationAndRotation(OutLocation, OutRotation, false, 0, ETeleportType::TeleportPhysics);
}