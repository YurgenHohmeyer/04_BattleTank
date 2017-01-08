// Copyright Yurgen Hohmeyer 2017

#pragma once

#include "GameFramework/Actor.h"
#include "MainCannonProjectile.generated.h"

UCLASS()
class BATTLETANK_UNREAL_API AMainCannonProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainCannonProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void LaunchProjectile(float Speed);

private:
	UProjectileMovementComponent* MainCannonProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr;
};
