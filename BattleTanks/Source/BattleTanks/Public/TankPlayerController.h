// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/World.h>
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	
	void AimTowardsCrosshair();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankAimingComponent * AimingComponent = nullptr;

private:
	

	bool GetSightRayHitLocation(FVector&);

	void GetWorldLookDirectionFromScreen(FVector &WorldLookDirection);

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float maxLookDistance = 10000000.f;
};
