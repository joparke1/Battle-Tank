// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto YawSpeed = RelativeSpeed * MaxMoveSpeed * GetWorld()->DeltaTimeSeconds;
	auto YawAmount = RelativeRotation.Yaw + YawSpeed;

	SetRelativeRotation(FRotator(0, YawAmount, 0));
}
