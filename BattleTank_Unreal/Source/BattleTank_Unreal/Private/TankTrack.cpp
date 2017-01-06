// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_Unreal.h"
#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle) {
	// auto Time = GetWorld()->GetTimeSeconds();
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Throttle: %f"), *Name, Throttle);

	// TODO clamp actualy throttle value so player can't over-drive
}
