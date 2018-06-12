// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTreds.h"


UFUNCTION(BlueprintCallable)
void UTankTreds::ApplyThrottle(float amount)
{
	auto MoveForce = GetForwardVector() * amount * MaxDriveForce;
	auto ForceLocation = GetComponentLocation();
	
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	RootComponent->AddForceAtLocation(MoveForce, ForceLocation);

	
}

