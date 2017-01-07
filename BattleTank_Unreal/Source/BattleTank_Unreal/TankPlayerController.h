// Copyright Yurgen Hohmeyer 2017

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

/**
* Responsible for helping the player aim.
*/
UCLASS()
class BATTLETANK_UNREAL_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);
	
private:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel so that shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	bool GetCrosshairTraceHit(FString &Objecthit, FVector &HitLocation);
};
