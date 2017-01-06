// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_UNREAL_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel so that shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	bool GetCrosshairTraceHit(FString &Objecthit, FVector &HitLocation);
};
