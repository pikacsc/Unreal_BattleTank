// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/TankAIController.h"
#include "Unreal_BattleTank/Public/TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Tank.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn * _InPawn)
{
	Super::SetPawn(_InPawn);
	if (_InPawn)
	{
		auto PossessedTank = Cast<ATank>(_InPawn);
		if (!ensure(PossessedTank)) { return; }

		//TODO Subscribe our local method to the tank's death event
		PossessedTank->m_OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}


void ATankAIController::OnPossedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Received!"));
}


// Called every frame
void ATankAIController::Tick(float _fDeltaTime)
{
	Super::Tick(_fDeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	// Move towards the player
	MoveToActor(PlayerTank, m_AcceptanceRadius); // TODO check radius is in cm

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}


