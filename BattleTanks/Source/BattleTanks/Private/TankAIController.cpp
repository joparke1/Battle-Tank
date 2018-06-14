// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>( GetWorld()->GetFirstPlayerController()->GetPawn());
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!ensure(PlayerTank && AimingComponent)) { return; }
	
	// TODO: move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim at the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// fire if ready
	//AITank->Fire();
}