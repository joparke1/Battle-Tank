// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Tank.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	owningTank = Cast<ATank>( GetOwner() );
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ensure(owningTank)) { return; }
	
	if (!owningTank->GetReloadComplete())
	{
		FiringState = EFiringState::Reloading;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool suggestedVelocitySuccess = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation,
									AimLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (suggestedVelocitySuccess)
	{
		auto LaunchDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(LaunchDirection);
	}
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector LaunchDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto LaunchRotator = LaunchDirection.Rotation();
	auto DeltaRotator = LaunchRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}



