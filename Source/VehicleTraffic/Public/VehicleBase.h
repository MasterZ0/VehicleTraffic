// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "VehicleBase.generated.h"

/**
 * WheeledVehicleAI : UWheeledVehicle : Pawn : Actor
 * CarAI : AIController : Controller : Actor
 * WheeledVehicleAI -> É um Pawn que pode ser possuido pelo CarAI
 */
UCLASS()
class VEHICLETRAFFIC_API AVehicleBase : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	AVehicleBase();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTreeComponent* BTC;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
