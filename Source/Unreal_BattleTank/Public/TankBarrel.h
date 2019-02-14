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
	void Elevate(float _DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float m_MaxDegreesPerSecond = 20; 

	UPROPERTY(EditAnywhere, Category = Setup)
		float m_MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
		float m_MinElevationDegrees = 0;


};
