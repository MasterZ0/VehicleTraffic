#pragma once

#include "Interfaces/Detectable.h"

#include "CoreMinimal.h"
#include <Components/SplineComponent.h>
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "TrafficLight.generated.h"

UENUM(BlueprintType)
enum class ETrafficState : uint8
{
	Red,
	Yellow,
	Green
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VEHICLETRAFFIC_API UTrafficLight : public UActorComponent, public IDetectable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Traffic Light")
	float YellowDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Traffic Light")
	float GreenDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Traffic Light")
	UPrimitiveComponent* TriggerComponent;

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Traffic Light")
	ETrafficState TrafficState;

	UPROPERTY(VisibleInstanceOnly, Category = "Traffic Light")
	float Timer;

	UStaticMeshComponent* Red;
	UStaticMeshComponent* Yellow;
	UStaticMeshComponent* Green;
	UStaticMeshComponent* CurrentLight;

public:
	UTrafficLight();

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Traffic Light")
	void Init(UStaticMeshComponent* InRed, UStaticMeshComponent* InYellow, UStaticMeshComponent* InGreen);

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Traffic Light")
	void Open();

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Traffic Light")
	ETrafficState GetTrafficState();

	UFUNCTION(BlueprintCallable, Category = "Vehicle Traffic\Traffic Light")
	bool TrafficClosed();

private:
	void OnComponentCreated() override;
	virtual void BeginPlay() override;
	void SwitchLight(UStaticMeshComponent* NewLight, ETrafficState State);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
