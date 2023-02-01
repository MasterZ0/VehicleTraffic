// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CarTriggerDetection.h"

UCarTriggerDetection::UCarTriggerDetection()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Front Detector"));
}

void UCarTriggerDetection::OnComponentCreated()
{
	Super::OnComponentCreated();

	USceneComponent* RootComponent = GetOwner()->GetRootComponent();
	BoxComponent->SetupAttachment(RootComponent);
}

void UCarTriggerDetection::BeginPlay()
{
	Super::BeginPlay();

	Obstacles = TArray<AActor*>();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBeginFrontDetector);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEndFrontDetector);
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
	UTrafficLight* Component = Cast<UTrafficLight>(OtherActor->GetComponentByClass(UTrafficLight::StaticClass()));
	if (IsValid(Component))
	{
		CurrentLight = Component;
	}
	else
	{
		Obstacles.Add(OtherActor);
	}
}

void UCarTriggerDetection::OnOverlapEndFrontDetector(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UTrafficLight* Component = Cast<UTrafficLight>(OtherActor->GetComponentByClass(UTrafficLight::StaticClass()));
	if (CurrentLight == Component)
	{
		CurrentLight = nullptr;
	}
	else
	{
		Obstacles.Remove(OtherActor);
	}
}

