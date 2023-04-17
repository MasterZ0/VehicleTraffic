// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TrafficLight.h"
#include "CarTriggerDetection.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VEHICLETRAFFIC_API UCarTriggerDetection : public USceneComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vehicle Traffic\AI")
	UPrimitiveComponent* PrimitiveComponent;

private:
	TArray<AActor*> Obstacles;
	UTrafficLight* CurrentLight;

public:
	UCarTriggerDetection();

	bool HasObstacle();

	UTrafficLight* GetTrafficLight();

protected:
	UFUNCTION()
	void OnOverlapBeginFrontDetector(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEndFrontDetector(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	void OnComponentCreated() override;
	virtual void BeginPlay() override;
};
