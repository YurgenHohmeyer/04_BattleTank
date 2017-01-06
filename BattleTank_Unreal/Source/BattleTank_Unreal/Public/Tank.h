// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Must be last include

// Forward declaration
class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class AMainCannonProjectile;

UCLASS()
class BATTLETANK_UNREAL_API ATank : public APawn
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FString ObjectHit, FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Weapons)
	void FireMainCannon();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AMainCannonProjectile> MainCannonProjectileBlueprint;

	// Projectile speed
	UPROPERTY(EditDefaultsOnly, Category = Weapons)
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Weapons)
	float ReloadTimeInSeconds = 3;

	// Local barrel reference for spawning projectile    
	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0;
};
