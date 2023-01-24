
#include "TrafficLight.h"

UTrafficLight::UTrafficLight()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	this->timer = 0.0f;
	this->trafficState = ETrafficState::Red;
}

void UTrafficLight::Init(UStaticMeshComponent* _red, UStaticMeshComponent* _yellow, UStaticMeshComponent* _green)
{
	// Inject objects
	this->red = _red;
	this->yellow = _yellow;
	this->green = _green;

	// Setup
	this->currentLight = this->red;
}

void UTrafficLight::Open()
{
	if (this->green == nullptr)
	{
		throw "Null lights";
	}

	this->timer = 0;
	SwitchLight(green, ETrafficState::Green);
}

void UTrafficLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Ignore red light
	if (this->trafficState == ETrafficState::Red)
		return;

	this->timer += DeltaTime;

	// Check for next state
	if (this->trafficState == ETrafficState::Green)
	{
		if (this->timer >= this->greenDuration)
		{
			SwitchLight(this->yellow, ETrafficState::Yellow);
		}
	}
	else // Yellow
	{
		if (this->timer >= this->greenDuration + this->yellowDuration)
		{
			SwitchLight(this->red, ETrafficState::Red);
		}
	}
}

void UTrafficLight::SwitchLight(UStaticMeshComponent* newLight, ETrafficState state)
{
	this->trafficState = state;
	this->currentLight->SetVisibility(false);
	this->currentLight = newLight;
	this->currentLight->SetVisibility(true);
}

ETrafficState UTrafficLight::GetTrafficState()
{
	return this->trafficState;
}

bool UTrafficLight::TrafficClosed()
{
	return this->trafficState == ETrafficState::Red;
}
