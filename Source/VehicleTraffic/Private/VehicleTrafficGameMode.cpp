// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleTrafficGameMode.h"
#include "VehicleTrafficPawn.h"
#include "VehicleTrafficHud.h"

AVehicleTrafficGameMode::AVehicleTrafficGameMode()
{
	DefaultPawnClass = AVehicleTrafficPawn::StaticClass();
	HUDClass = AVehicleTrafficHud::StaticClass();
}
