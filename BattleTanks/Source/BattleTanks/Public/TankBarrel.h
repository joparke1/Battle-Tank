// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxMoveSpeed = 20.0f;
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxMoveAngle = 30.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinMoveAngle = 0.0f;
};
