// Fill out your copyright notice in the Description page of Project Settings.


#include "CarAI.h"


ACarAI::ACarAI(const FObjectInitializer& ObjectInitializer) 
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTree Component"));
}


void ACarAI::OnPossess(APawn* InPawn)
{

}