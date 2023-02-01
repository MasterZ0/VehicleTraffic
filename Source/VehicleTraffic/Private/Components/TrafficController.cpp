#include "Components/TrafficController.h"

UTrafficController::UTrafficController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTrafficController::BeginPlay()
{
	this->traffics = TArray<UTrafficLight*>();
}

void UTrafficController::AddTrafficLightActor(AActor* actor)
{
	if (actor == nullptr) 
	{
		throw "Null Reference";
	}

	UTrafficLight* trafficLight = Cast<UTrafficLight>(actor->GetComponentByClass(UTrafficLight::StaticClass()));

	if (trafficLight == nullptr)
	{
		throw "Null Component";
	}

	this->traffics.Add(trafficLight);

	// Check if has any TrafficLight open
	if (!this->started)
	{
		this->started = true;
		this->traffics[0]->Open();
	}
}

void UTrafficController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!this->started)
		return;

	// Check if the current is closed
	if (this->traffics[this->currentIndex]->TrafficClosed())
	{
		// Update index
		this->currentIndex++;

		if (this->currentIndex >= this->traffics.Num()) {
			this->currentIndex = 0;
		}

		// Open next traffic light
		this->traffics[currentIndex]->Open();
	}
}