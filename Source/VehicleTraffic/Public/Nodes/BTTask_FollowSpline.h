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
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector SplineKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector OffsetKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector SpeedKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector InverseKey;

	UBTTask_FollowSpline(const FObjectInitializer& ObjectInitializer);

	void Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void Tick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	AActor* Actor;
	USplineComponent* Spline;
	FVector Offset;

	float TravelDistance;
	float Speed;
	bool Inverse;
};
