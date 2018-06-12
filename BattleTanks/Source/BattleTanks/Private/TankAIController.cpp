// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AITank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>( GetWorld()->GetFirstPlayerController()->GetPawn());
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerTank)
	{
		// TODO: move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim at the player
		AITank->AimAt(PlayerTank->GetActorLocation());

		// fire if ready
		//AITank->Fire();
	}
}