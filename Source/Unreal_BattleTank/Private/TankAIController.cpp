// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/TankAIController.h"
#include "Unreal_BattleTank/Public/Tank.h"
#include "Engine/World.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float _fDeltaTime)
{
	Super::Tick(_fDeltaTime);
	//Get PlayerTank
	m_PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	//Get Controlled Tank
	m_AITank = Cast<ATank>(GetPawn());


	if (ensure(m_PlayerTank))
	{
		// TODO Move towards the player
		MoveToActor(m_PlayerTank, m_AcceptanceRadius);

		// Aim towards the player 
		m_AITank->AimAt(m_PlayerTank->GetActorLocation());
		m_AITank->Fire();
	}

}


