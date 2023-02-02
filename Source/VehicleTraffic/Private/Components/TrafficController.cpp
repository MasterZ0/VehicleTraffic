#include "Components/TrafficController.h"

UTrafficController::UTrafficController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTrafficController::BeginPlay()
{
	Traffics = TArray<UTrafficLight*>();
	CurrentIndex = -1;
}

void UTrafficController::AddTrafficLightActor(AActor* OwnerActor)
{
	if (!OwnerActor)
		throw "Null Actor";

	UTrafficLight* TrafficLight = Cast<UTrafficLight>(OwnerActor->GetComponentByClass(UTrafficLight::StaticClass()));

	AddTrafficLight(TrafficLight);
}

void UTrafficController::AddTrafficLight(UTrafficLight* NewTrafficLight)
{
	if (!NewTrafficLight)
		throw "Null TrafficLight";

	Traffics.Add(NewTrafficLight);

	// Check if has any TrafficLight open
	if (CurrentIndex == -1)
	{
		CurrentIndex = 0;
		Traffics[0]->Open();
	}
}

void UTrafficController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentIndex == -1)
		throw "Missing Traffic Lights, you must add some";

	// Check if the current is closed
	if (Traffics[CurrentIndex]->TrafficClosed())
	{
		// Update index
		CurrentIndex++;

		if (CurrentIndex >= Traffics.Num()) 
		{
			CurrentIndex = 0;
		}

		// Open next traffic light
		Traffics[CurrentIndex]->Open();
	}
}