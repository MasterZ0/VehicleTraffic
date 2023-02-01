// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "AIController.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

#include "Classes/BezierCurve.h"
#include "Functions/SplineLibrary.h"
#include "BTTask_ActionTaskBase.h"

#include "BTTask_SwitchSpline.generated.h"
/**
 *
 */
UCLASS()
class VEHICLETRAFFIC_API UBTTask_SwitchSpline : public UBTTask_ActionTaskBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector SplineKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector OffsetKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector CurveSmoothKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector SpeedKey;

	USplineComponent* Spline;
	FVector Offset;
	float CurveSmooth;
	float Speed;

	AActor* Actor;
	float TravelDistance;
	FBezierCurve BezierCurve;

	UBTTask_SwitchSpline(const FObjectInitializer& ObjectInitializer);

	void Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void Tick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float Delta) override;
};
