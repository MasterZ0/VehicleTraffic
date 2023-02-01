// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionTask.generated.h"

UENUM(BlueprintType)
enum class ActionState : uint8
{
	Stopped UMETA(Hidden),
	Running,
	Success,
	Failure
};

UCLASS(BlueprintType)
class UActionTask : public UObject
{
	GENERATED_BODY()

public:
	UActionTask();

private:
	ActionState CurrentState;

protected:
	void EndTask(bool Success);

	virtual void StartTask() {}
	virtual void TickTask(float Delta) {}
	virtual void StopTask() {}

public:
	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Tasks", Meta = (ExpandEnumAsExecs = "Branches"))
	void RunTask(ActionState& Branches);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Tasks")
	void Reset();
};