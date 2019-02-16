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
		// TODO Move towards the player
	//Get PlayerTank
	m_PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	//Get Controlled Tank
	m_AITank = Cast<ATank>(GetPawn());


	if (!m_AITank || !m_PlayerTank) { return; }

	// Aim towards the player 
	m_AITank->AimAt(m_PlayerTank->GetActorLocation());
	m_AITank->Fire();

}


