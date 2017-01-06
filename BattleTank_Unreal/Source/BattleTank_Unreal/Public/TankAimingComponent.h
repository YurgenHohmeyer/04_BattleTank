// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;
class UTankTurret;

// Holds turrets and barrels properties and movement methods
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_UNREAL_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FString ObjectHit, FVector HitLocation, float LaunchSpeed);

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
	void AimTurretAndBarrel(FVector AimDirection);
};
