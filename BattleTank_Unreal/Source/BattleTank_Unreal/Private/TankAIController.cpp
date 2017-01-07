// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_Unreal.h"
#include "Public/Tank.h"
#include "Public/TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime );

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerTank)) {
		// Move Towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

		// Aim towards the player
		ControlledTank->AimAt("", PlayerTank->GetActorLocation());

		ControlledTank->FireMainCannon(); // TODO limit firing rate

	}
}