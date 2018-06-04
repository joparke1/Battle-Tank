// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* playerTank = GetPlayerTank();

	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found Player Controller: %s"), *(playerTank->GetName()))
	}
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		// TODO: move towards the player

		// Aim at the player
		GetAITank()->AimAt(GetPlayerTank()->GetActorLocation());

		// fire if ready
	}
}

ATank* ATankAIController::GetAITank() const
{

	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!playerPawn)
	{
		return nullptr;
	}

	return Cast<ATank>(playerPawn);
}
