// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_Unreal.h"
#include "MainCannonProjectile.h"


// Sets default values
AMainCannonProjectile::AMainCannonProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCannonProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCannonProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

