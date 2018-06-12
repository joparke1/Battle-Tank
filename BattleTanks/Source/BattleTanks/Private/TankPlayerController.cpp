// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

UFUNCTION(BlueprintCallable, Category = Setup)
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	// if no tank found, leave
	if(!GetControlledTank()) 
	{
		return;
	}

	FVector hitLocation(0.f, 0.f, 0.f);
	if (GetSightRayHitLocation(hitLocation))
	{
		GetControlledTank()->AimAt(hitLocation);
	}
	else
	{
		GetControlledTank()->AimAt(FVector(0));
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
