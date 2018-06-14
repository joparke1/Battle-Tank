// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTreds.h"

UFUNCTION(BlueprintCallable, Category = Setup)
void UTankMovementComponent::Initialize(UTankTreds* LeftTredToSet, UTankTreds* RightTredToSet)
{
	if (!ensure(LeftTredToSet && RightTredToSet)) { return; }

	LeftTred = LeftTredToSet;
	RightTred = RightTredToSet;
}

UFUNCTION(BlueprintCallable, Category = Input)
void UTankMovementComponent::ForwardBackwardImpulse(float amount)
{
	LeftTred->ApplyThrottle(amount);
	RightTred->ApplyThrottle(amount);
}

UFUNCTION(BlueprintCallable, Category = Input)
void UTankMovementComponent::Rotate(float amount)
{
	RightTred->ApplyThrottle(amount);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto MoveDirection = MoveVelocity.GetSafeNormal();
	auto AIForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();

	auto FowardBackwardMovement = FVector::DotProduct(AIForwardDirection, MoveDirection);
	auto RotateVector = FVector::CrossProduct(AIForwardDirection, MoveDirection);

	ForwardBackwardImpulse(FowardBackwardMovement);
	Rotate(RotateVector.Z);
}
