// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector AimLocation)
{
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed);
}

UFUNCTION(BlueprintCallable, Category = Setup)
void ATank::Fire()
{
	auto bReloadComplete = GetReloadComplete();
	if (Barrel && bReloadComplete)
	{
		
		auto FiredProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		FiredProjectile->Launch(LaunchSpeed);

		LastLaunchTime = GetWorld()->GetTimeSeconds();
	}
}

void ATank::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent->Initialize(BarrelToSet, TurretToSet);
}


bool ATank::GetReloadComplete()
{
	return (GetWorld()->GetTimeSeconds() - LastLaunchTime) >= ReloadTime;
}
