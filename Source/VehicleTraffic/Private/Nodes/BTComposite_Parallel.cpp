// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/BTComposite_Parallel.h"


UBTComposite_Parallel::UBTComposite_Parallel(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Parallel";
	bUseChildExecutionNotify = true;
	bUseNodeDeactivationNotify = true;
	bUseDecoratorsDeactivationCheck = true;
	bApplyDecoratorScope = true;
}

int32 UBTComposite_Parallel::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	FString string = FString();
	string = "GetNextChildHandler: " + FString::FromInt(PrevChild) + " // " + FString::FromInt(LastResult);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, string);


    if (PrevChild == BTSpecialChild::NotInitialized)
    {
		return PrevChild + 1;
    }
	else if (LastResult != EBTNodeResult::InProgress) // Stop?
	{
		return BTSpecialChild::ReturnToParent;
	}

	return PrevChild + 1;
}

void UBTComposite_Parallel::NotifyChildExecution(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, int32 ChildIdx, EBTNodeResult::Type& NodeResult) const
{

	FString string = FString();
	string = "Execution[" + FString::FromInt(ChildIdx) + "] =  " + Children[ChildIdx].ChildTask->GetNodeName() + " // " + FString::FromInt(NodeResult);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, string);


	if (ChildIdx + 1 < GetChildrenNum())
	{
		EBTTaskStatus::Type Status = OwnerComp.GetTaskStatus(Children[ChildIdx].ChildTask);
		
		if (NodeResult == EBTNodeResult::Type::InProgress)
		{
			string = "-Register Parallel[" + FString::FromInt(ChildIdx) + "]";
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, string);


			const int32 MyInstanceIdx = OwnerComp.FindInstanceContainingNode(this);

			OwnerComp.RegisterParallelTask(Children[ChildIdx].ChildTask);

			// Add Next child
			OwnerComp.RequestExecution((UBTCompositeNode*)this, MyInstanceIdx, Children[ChildIdx + 1].ChildTask, ChildIdx + 1, NodeResult);
		}
		else // Status == EBTTaskStatus::Active
		{

			string = "-Unregister Parallel[" + FString::FromInt(ChildIdx) + "]";
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, string);

			FBehaviorTreeSearchData FakeSearchData(OwnerComp);
			NotifyDecoratorsOnDeactivation(FakeSearchData, ChildIdx, NodeResult); // Is this necessary?
			// TODO: Force deactivation 

			const int32 MyInstanceIdx = OwnerComp.FindInstanceContainingNode(this);
			OwnerComp.UnregisterParallelTask(Children[ChildIdx].ChildTask, MyInstanceIdx);

			//RequestDelayedExecution(OwnerComp, NodeResult); // Force finish
		}
	}
}

void UBTComposite_Parallel::NotifyNodeActivation(FBehaviorTreeSearchData& SearchData) const
{
	const uint16 ActiveInstanceIdx = SearchData.OwnerComp.GetActiveInstanceIdx();

	FString string = FString();
	string = "Activation: " + ActiveInstanceIdx;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, string);
}

void UBTComposite_Parallel::NotifyNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult) const
{
	const uint16 ActiveInstanceIdx = SearchData.OwnerComp.GetActiveInstanceIdx();

	FString string = FString();
	string = "Deactivation: " + FString::FromInt(NodeResult) + " // " + ActiveInstanceIdx;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, string);
}

bool UBTComposite_Parallel::CanPushSubtree(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, int32 ChildIdx) const
{
	return true;
}