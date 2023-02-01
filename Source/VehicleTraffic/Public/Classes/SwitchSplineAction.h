// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/ActionTask.h"
#include "Classes/BezierCurve.h"
#include "Functions/SplineLibrary.h"
#include "Components/SplineComponent.h"
#include "SwitchSplineAction.generated.h"

/**
 * 
 */

UCLASS(DefaultToInstanced, EditInlineNew, Blueprintable)
class USwitchSplineAction : public UActionTask
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
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurveSmooth;

private:
	FBezierCurve BezierCurve;

	FVector ResultLocation;
	FRotator ResultRotation;

	float TravelDistance;

public:
	UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Branches"))
	void RunSwitchSpline(USplineComponent* InSpline, AActor* InActor, FVector InOffset, float InSpeed, float InCurveSmooth, 
		ActionState& Branches, FVector& OutLocation, FRotator& OutRotation);

private:
	void StartTask() override;
	void TickTask(float Delta) override;
};