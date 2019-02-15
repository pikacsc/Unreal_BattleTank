// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class UNREAL_BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float _RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float m_MaxDegreesPerSecond = 10; 

	UPROPERTY(EditAnywhere, Category = Setup)
		float m_MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
		float m_MinElevationDegrees = 0;


};
