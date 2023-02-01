// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TrafficLight.h"
#include "CarTriggerDetection.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VEHICLETRAFFIC_API UCarTriggerDetection : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Vehicle Traffic\AI")
	UBoxComponent* BoxComponent;

private:
	TArray<AActor*> Obstacles;
	UTrafficLight* CurrentLight;

public:
	UCarTriggerDetection();

	bool HasObstacle();

	UTrafficLight* GetTrafficLight();

	void OnComponentCreated() override;

protected:
	virtual void BeginPlay() override;

	void OnOverlapBeginFrontDetector(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnOverlapEndFrontDetector(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
