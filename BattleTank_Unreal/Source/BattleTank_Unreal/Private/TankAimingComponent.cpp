// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_Unreal.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/TankAimingComponent.h"




// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FString ObjectHit, FVector HitLocation, float LaunchSpeed) {
	if (!Barrel) { return; }
	if (!Turret) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	// Calculate OutLaunchVelocity
	bool bHaveAimingSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Param must be present to prevent bug
	);

	if (bHaveAimingSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		AimTurretAndBarrel(AimDirection);
	} // No aim solution found
} 

void UTankAimingComponent::AimTurretAndBarrel(FVector AimDirection) {
	// Work out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.GetNormalized().Pitch);

	Turret->Rotate(DeltaRotator.GetNormalized().Yaw);
}
