// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"



void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto PitchSpeed = RelativeSpeed * MaxMoveSpeed * GetWorld()->DeltaTimeSeconds;
	auto PitchAmount = RelativeRotation.Pitch + PitchSpeed;
	PitchAmount = FMath::Clamp<float>(PitchAmount, MinMoveAngle, MaxMoveAngle);
	
	SetRelativeRotation(FRotator(PitchAmount, 0, 0));
}