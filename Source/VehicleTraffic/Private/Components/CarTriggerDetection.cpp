// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CarTriggerDetection.h"

UCarTriggerDetection::UCarTriggerDetection()
{
	//PrimitiveComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Front Detector"));
}

void UCarTriggerDetection::OnComponentCreated()
{
	Super::OnComponentCreated();

	USceneComponent* Root = GetOwner()->GetRootComponent();

	if (PrimitiveComponent) 
	{
		PrimitiveComponent->SetupAttachment(Root);
	}
}

void UCarTriggerDetection::BeginPlay()
{
	Super::BeginPlay();

	if (!PrimitiveComponent)
		return;

	Obstacles = TArray<AActor*>();

	PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBeginFrontDetector);
	PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEndFrontDetector);
}

bool UCarTriggerDetection::HasObstacle()
{
	return Obstacles.Num() > 0;
}

UTrafficLight* UCarTriggerDetection::GetTrafficLight()
{
	return CurrentLight;
}

void UCarTriggerDetection::OnOverlapBeginFrontDetector(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->GetClass()->ImplementsInterface(UDetectable::StaticClass()))
		return;

	UActorComponent* Component = OtherActor->GetComponentByClass(UTrafficLight::StaticClass());
	if (IsValid(Component))
	{
		CurrentLight = Cast<UTrafficLight>(Component);
	}
	else if (!Obstacles.Contains(OtherActor))
	{
		Obstacles.Add(OtherActor);
	}
}

void UCarTriggerDetection::OnOverlapEndFrontDetector(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->GetClass()->ImplementsInterface(UDetectable::StaticClass()))
		return;

	UActorComponent* Component = OtherActor->GetComponentByClass(UTrafficLight::StaticClass());
	if (CurrentLight && CurrentLight == Component)
	{
		CurrentLight = nullptr;
	}
	else
	{
		Obstacles.Remove(OtherActor);
	}
}

