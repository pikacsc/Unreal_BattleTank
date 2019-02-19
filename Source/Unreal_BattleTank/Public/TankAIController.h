// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float _fDeltaTime) override;

	// How close can the AI tank get to the player
	float  m_AcceptanceRadius = 3000.f;



};
