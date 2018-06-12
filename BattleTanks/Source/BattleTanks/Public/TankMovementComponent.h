// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTreds;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTreds* LeftTredToSet, UTankTreds* RightTredToSet);
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void ForwardBackwardImpulse(float amount);

	UFUNCTION(BlueprintCallable, Category = Input)
	void Rotate(float amount);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTreds * LeftTred = nullptr;
	UTankTreds* RightTred = nullptr;
};
