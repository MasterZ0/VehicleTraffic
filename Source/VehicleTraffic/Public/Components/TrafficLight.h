#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include <Components/SplineComponent.h>
#include "TrafficLight.generated.h"

UENUM(BlueprintType)
enum class ETrafficState : uint8
{
	Red,
	Yellow,
	Green
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VEHICLETRAFFIC_API UTrafficLight : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TrafficLight")
		float yellowDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TrafficLight")
		float greenDuration;

private:
	UPROPERTY(VisibleInstanceOnly, Category = "TrafficLight")
		ETrafficState trafficState;

	UPROPERTY(VisibleInstanceOnly, Category = "TrafficLight")
		float timer;

	UStaticMeshComponent* red;
	UStaticMeshComponent* yellow;
	UStaticMeshComponent* green;
	UStaticMeshComponent* currentLight;

public:
	UTrafficLight();

	UFUNCTION(BlueprintCallable, Category = "TrafficLight")
		void Init(UStaticMeshComponent* red, UStaticMeshComponent* yellow, UStaticMeshComponent* green);

	UFUNCTION(BlueprintCallable, Category = "TrafficLight")
		void Open();

	UFUNCTION(BlueprintCallable, Category = "TrafficLight")
		ETrafficState GetTrafficState();

	UFUNCTION(BlueprintCallable, Category = "TrafficLight")
		bool TrafficClosed();

	UFUNCTION(BlueprintCallable, Category = "TrafficLight")
		void SwitchLight(UStaticMeshComponent* newLight, ETrafficState state);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
