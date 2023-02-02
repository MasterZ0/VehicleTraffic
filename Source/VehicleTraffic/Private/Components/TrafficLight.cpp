
#include "Components/TrafficLight.h"

UTrafficLight::UTrafficLight()
{
	PrimaryComponentTick.bCanEverTick = true;
	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Front Detector"));
}

void UTrafficLight::OnComponentCreated()
{
	Super::OnComponentCreated();

	USceneComponent* Root = GetOwner()->GetRootComponent();

	if (TriggerComponent)
	{
		TriggerComponent->SetupAttachment(Root);
	}
}

void UTrafficLight::BeginPlay()
{
	TrafficState = ETrafficState::Red;
}

void UTrafficLight::Init(UStaticMeshComponent* InRed, UStaticMeshComponent* InYellow, UStaticMeshComponent* InGreen)
{
	// Inject objects
	Red = InRed;
	Yellow = InYellow;
	Green = InGreen;

	// Setup
	CurrentLight = Red;
}

void UTrafficLight::Open()
{
	if (!Green)
	{
		throw "UTrafficLight: Null lights";
	}

	Timer = 0;
	SwitchLight(Green, ETrafficState::Green);
}

void UTrafficLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Ignore red light
	if (TrafficState == ETrafficState::Red)
		return;

	Timer += DeltaTime;

	// Check for next state
	if (TrafficState == ETrafficState::Green)
	{
		if (Timer >= GreenDuration)
		{
			SwitchLight(Yellow, ETrafficState::Yellow);
		}
	}
	else // Yellow
	{
		if (Timer >= GreenDuration + YellowDuration)
		{
			SwitchLight(Red, ETrafficState::Red);
		}
	}
}

void UTrafficLight::SwitchLight(UStaticMeshComponent* NewLight, ETrafficState State)
{
	TrafficState = State;
	CurrentLight->SetVisibility(false);
	CurrentLight = NewLight;
	CurrentLight->SetVisibility(true);
}

ETrafficState UTrafficLight::GetTrafficState()
{
	return TrafficState;
}

bool UTrafficLight::TrafficClosed()
{
	return TrafficState == ETrafficState::Red;
}