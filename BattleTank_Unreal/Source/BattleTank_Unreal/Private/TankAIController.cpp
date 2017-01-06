// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_Unreal.h"
#include "Public/Tank.h"
#include "Public/TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	
	return ;
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime );

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank) { return nullptr; }

	if (GetPlayerTank()) {
		// TODO Move Towards the player

		// Aim towards the player
		FString PlayerTankName = GetPlayerTank()->GetName();
		GetControlledTank()->AimAt(PlayerTankName, GetPlayerTank()->GetActorLocation());

		GetControlledTank()->FireMainCannon();

	}
}