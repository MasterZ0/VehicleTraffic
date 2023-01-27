// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTTask_ActionTaskBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

#include "BTTask_WaitUntilTrigger.generated.h"
/**
 * 
 */
UCLASS()
class VEHICLETRAFFIC_API UBTTask_WaitUntilTrigger : public UBTTask_ActionTaskBase
{
	GENERATED_BODY()

public:

	UBTTask_WaitUntilTrigger(const FObjectInitializer& ObjectInitializer);

	void Start(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void Stop() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	UBoxComponent* TriggerBox;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
