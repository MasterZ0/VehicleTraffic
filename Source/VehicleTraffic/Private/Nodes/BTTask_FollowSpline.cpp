// Fill out your copyright notice in the Description page of Project Settings.

#include "Nodes/BTTask_FollowSpline.h"

UBTTask_FollowSpline::UBTTask_FollowSpline(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "Follow Spline";
}

EBTNodeResult::Type UBTTask_FollowSpline::Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* MyController = OwnerComp.GetAIOwner();

	if (!MyController || !MyBlackboard)
		return EBTNodeResult::Type::Failed;

	//  OwnerComp.GetAIOwner()->GetPawn()
	Actor = OwnerComp.GetOwner();

	FRotator OutRotation = FRotator();

	USplineLibrary::GetPathDirection(Spline, Actor->GetActorLocation(), Actor->GetActorRotation(), OutRotation, TravelDistance, Inverse);

	Actor->SetActorRotation(OutRotation);

	return EBTNodeResult::Type::InProgress;
}

EBTNodeResult::Type UBTTask_FollowSpline::Update(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	float Delta = OwnerComp.GetWorld()->DeltaTimeSeconds;

	FVector OutLocation = FVector();
	FRotator OutRotation = FRotator();

	USplineLibrary::FollowPath(Spline, Offset, Speed, TravelDistance, Delta, Inverse, OutLocation, OutRotation, TravelDistance);

	Actor->SetActorLocation(OutLocation);
	Actor->SetActorRotation(OutRotation);

	return EBTNodeResult::Type::Succeeded;
}