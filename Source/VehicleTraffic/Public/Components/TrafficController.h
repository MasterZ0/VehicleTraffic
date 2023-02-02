#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrafficLight.h"
#include "TrafficController.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VEHICLETRAFFIC_API UTrafficController : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<UTrafficLight*> Traffics;
	int CurrentIndex;

public:
	UTrafficController();

	UFUNCTION(BlueprintCallable, Category = "TrafficLight")
	void AddTrafficLightActor(AActor* OwnerActor);


	UFUNCTION(BlueprintCallable, Category = "TrafficLight")
	void AddTrafficLight(UTrafficLight* NewTrafficLight);

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
