// Copyright Yurgen Hohmeyer 2017

#include "BattleTank_Unreal.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/MainCannonProjectile.h"
#include "Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay() {
	LastFireTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds) {
		FiringStatus = EFiringStatus::Reloading;
	}
	// TODO handle aiming and locked states
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FString ObjectHit, FVector HitLocation) {
	if (!ensure(Barrel && Turret)) { return; }

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
	if (!ensure(Barrel && Turret)) { return; }
	// Work out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.GetNormalized().Pitch);

	Turret->Rotate(DeltaRotator.GetNormalized().Yaw);
}

void UTankAimingComponent::FireMainCannon() {
	if (FiringStatus != EFiringStatus::Reloading) {

		// Spawn a projectile at the socket location on the barrel
		if (!ensure(Barrel)) { return; }
		if (!ensure(MainCannonProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AMainCannonProjectile>(
			MainCannonProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
	}
}
