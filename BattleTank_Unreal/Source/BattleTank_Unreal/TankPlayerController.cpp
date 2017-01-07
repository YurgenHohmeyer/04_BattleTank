// Copyright Yurgen Hohmeyer 2017

#include "BattleTank_Unreal.h"
#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller cannot find aiming component at BeginPlay."))
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
	if (!ensure(GetControlledTank())) { return; }

	FVector HitLocation;
	FString ObjectHit;

	if (GetCrosshairTraceHit(ObjectHit, HitLocation)) {
		GetControlledTank()->AimAt(ObjectHit, HitLocation);
	}
}

bool ATankPlayerController::GetCrosshairTraceHit(FString &ObjectHit, FVector &HitLocation) {
	// Get Viewport Size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	bool bHit;
	FVector2D CrosshairPosition = FVector2D(ViewportSizeX / 2, ViewportSizeY / 3);
	FHitResult HitResult;

	bHit = GetHitResultAtScreenPosition(CrosshairPosition, ECollisionChannel::ECC_Visibility, false, HitResult);

	if (bHit) {
		HitLocation = HitResult.ImpactPoint;
		ObjectHit = HitResult.GetActor()->GetName();
		return bHit;
	}
	HitLocation = FVector(0);
	return false;
}
