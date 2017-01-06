// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_Unreal.h"
#include "Public/TankTurret.h"



void UTankTurret::Rotate(float RelativeSpeed) {
	// Move the turret the right amount this frame
	// Given max turn speed and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}
