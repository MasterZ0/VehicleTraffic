// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficLight.h"

// Sets default values for this component's properties
UTrafficLight::UTrafficLight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTrafficLight::Init(UStaticMeshComponent* _red, UStaticMeshComponent* _yellow, UStaticMeshComponent* _green)
{
	this->red = _red;
	this->yellow = _yellow;
	this->green = _green;

	this->currentLight = _red;
	State = ETrafficState::Red;
}

void UTrafficLight::SwitchLight(UStaticMeshComponent* newLight, ETrafficState state)
{
	State = state;
	currentLight->SetVisibility(false);
	currentLight = newLight;
	currentLight->SetVisibility(true);
}

void UTrafficLight::Open()
{
	// Switch to green light
	//SwitchLight(green, ETrafficState::Green);
	// Wait for greenDuration seconds
	FTimerHandle TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, SwitchYellow, greenDuration, false);
}

void SwitchYellow(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{


	// ...
}

// Called every frame
void UTrafficLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

