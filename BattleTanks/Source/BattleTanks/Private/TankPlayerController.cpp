// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(AimingComponent)) { return; }

	FVector hitLocation(0.f, 0.f, 0.f);
	if (GetSightRayHitLocation(hitLocation))
	{
		AimingComponent->AimAt(hitLocation);
	}
	else
	{
		AimingComponent->AimAt(FVector(0));
	}

	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation)
{
	FVector WorldLookDirection;

	GetWorldLookDirectionFromScreen(WorldLookDirection);

	
	FHitResult hitResult;
	FVector StartLoction = PlayerCameraManager->GetCameraLocation();
	FVector lookEnd = StartLoction + (WorldLookDirection * maxLookDistance);
	
	// get raycast through crosshair and see if it hits anything
	if (GetWorld()->LineTraceSingleByChannel(hitResult, StartLoction, lookEnd, ECollisionChannel::ECC_Visibility))
	{
		// update OutHitLocation
		OutHitLocation = hitResult.Location;
		return true;
	}
	
	OutHitLocation = FVector(0.f);
	return false;
}

void ATankPlayerController::GetWorldLookDirectionFromScreen(FVector &WorldLookDirection)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);

	// change 2d to world space
	FVector CameraLocation;

	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, WorldLookDirection);
}
