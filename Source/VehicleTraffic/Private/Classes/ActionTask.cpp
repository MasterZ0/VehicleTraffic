// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/ActionTask.h"

UActionTask::UActionTask() 
{
	CurrentState = ActionState::Stopped;
}

void UActionTask::RunTask(ActionState& Branches)
{
	// Check change state
	if (CurrentState == ActionState::Stopped)
	{
		// Start New Task
		CurrentState = ActionState::Running;
		StartTask();

		// Check if finish after StartTask
		if (CurrentState != ActionState::Running)
		{
			StopTask();
			Branches = CurrentState;
			return;
		}
	}

	float Delta = GetWorld()->IsPaused() ? 0.f : GetWorld()->GetDeltaSeconds();
	TickTask(Delta);

	// Check if finish after TickTask
	if (CurrentState != ActionState::Running)
	{
		StopTask();
	}

	Branches = CurrentState;
}

void UActionTask::EndTask(bool Success)
{
	CurrentState = Success ? ActionState::Success : ActionState::Failure;
}

void UActionTask::Reset()
{
	if (CurrentState == ActionState::Running)
	{
		// Abort
		StopTask();
	}

	CurrentState = ActionState::Stopped;
}