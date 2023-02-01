// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/ActionTask.h"
#include "Components/SplineComponent.h"
#include "Functions/SplineLibrary.h"
#include "FollowSplineAction.generated.h"

/**
 * 
 */

UCLASS(DefaultToInstanced, EditInlineNew, Blueprintable)
class UFollowSplineAction : public UActionTask
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Actor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* Spline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TravelDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool InverseSpline;

private:
	FVector ResultLocation;
	FRotator ResultRotation;

public:
	UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Branches"))
	void RunFollowSpline(USplineComponent* InSpline, AActor* InActor, FVector InOffset, float InSpeed,
		ActionState& Branches, FVector& OutLocation, FRotator& OutRotation, float& OutTravelDistance, bool& OutInverseSpline);

private:
	void StartTask() override;
	void TickTask(float Delta) override;
};