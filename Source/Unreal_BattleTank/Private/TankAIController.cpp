// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/TankAIController.h"

#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found Player: %s"), *(PlayerTank->GetName()));
	}
}

// Called every frame
void ATankAIController::Tick(float _fDeltaTime)
{
	Super::Tick(_fDeltaTime);
	if (GetPlayerTank())
	{
		// TODO Move towards the player
		
		// Aim towards the player 
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire if ready
	}
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}