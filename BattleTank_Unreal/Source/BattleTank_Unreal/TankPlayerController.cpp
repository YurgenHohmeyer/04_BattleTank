// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_Unreal.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank."));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

// Tick
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Our param
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
			// TODO tell controlled tank to aim at this point.
	}
}
// Get world location of line trace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that LookDirection and see what we hit (up to a max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetControlledPawn());
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility,
		CollisionParams)
		) {
		HitLocation = HitResult.Location;
		return true;
	}
	return false;	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}
