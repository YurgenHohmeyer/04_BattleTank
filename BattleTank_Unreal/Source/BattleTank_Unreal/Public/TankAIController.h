// Copyright Yurgen Hohmeyer 2017

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_UNREAL_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close can the AI get?
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;
	
private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
