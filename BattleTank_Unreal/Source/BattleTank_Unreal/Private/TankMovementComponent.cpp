// Copyright Yurgen Hohmeyer 2017

#include "BattleTank_Unreal.h"
#include "Public/TankTrack.h"
#include "Public/TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	// No need to call super as we're replacing the functionality

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention);
	IntendTurnRight(RightThrow.Z);
}


void UTankMovementComponent::IntendMoveForward(float Throw) {
	// Protect Pointers
	if (!LeftTrack || !RightTrack) { return; }
	// Clamp throttle values to disallow a doubled speed from two different control inputs
	Throw = FMath::Clamp<float>(Throw, -1, +1);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	// Protect Pointers
	if (!LeftTrack || !RightTrack) { return; }
	// Clamp throttle values to disallow a doubled speed from two different control inputs
	Throw = FMath::Clamp<float>(Throw, -1, +1);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
