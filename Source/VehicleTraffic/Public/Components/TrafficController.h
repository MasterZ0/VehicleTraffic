#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrafficLight.h"
#include "TrafficController.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VEHICLETRAFFIC_API UTrafficController : public UActorComponent
{
	GENERATED_BODY()

public:
	TArray<UTrafficLight*> traffics;

private:
	int currentIndex;
	bool started;

public:
	UTrafficController();

	UFUNCTION(BlueprintCallable, Category = "TrafficLight")
		void AddTrafficLightActor(AActor* actor);

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
