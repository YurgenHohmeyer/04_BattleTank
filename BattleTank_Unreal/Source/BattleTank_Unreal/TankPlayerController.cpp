// Copyright Yurgen Hohmeyer 2017

#include "BattleTank_Unreal.h"
#include "Public/TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

// Tick
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; } // If not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;
	FString ObjectHit;
	bool bGotHitLocation = GetCrosshairTraceHit(ObjectHit, HitLocation);
	if (bGotHitLocation) {
		AimingComponent->AimAt(ObjectHit, HitLocation);
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
