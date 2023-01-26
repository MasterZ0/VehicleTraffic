// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "AIController.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

#include "Functions/SplineLibrary.h"
#include "BTTask_ActionTaskBase.h"

#include "BTTask_FollowSpline.generated.h"
/**
 * 
 */
UCLASS()
class VEHICLETRAFFIC_API UBTTask_FollowSpline : public UBTTask_ActionTaskBase
{
	GENERATED_BODY()
	
public:

	UBTTask_FollowSpline(const FObjectInitializer& ObjectInitializer);

	EBTNodeResult::Type Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type Update(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	float TravelDistance;
	bool Inverse;
	USplineComponent* Spline;
	AActor* Actor;

	FVector Offset;
	float Speed;
};
