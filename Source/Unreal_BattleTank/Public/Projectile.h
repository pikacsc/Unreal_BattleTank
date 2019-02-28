// Copyrights JasonChoi(SEONG_CHAN) 2019

#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"


class UTankProjectileMovementComponent;

UCLASS()
class UNREAL_BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LaunchProjectile(float _fSpeed);


private:
	UTankProjectileMovementComponent* m_TankProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* m_CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* m_LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* m_ImpactBlast = nullptr;
	

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent*	  m_ExplosionForce = nullptr;


	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UAudioComponent* m_FireSound;

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UAudioComponent* m_ExplosionSound;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float				m_fDestroyDelay = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float				m_fProjectileDamage = 20.f;


	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit);
	
	UFUNCTION()
	void OnTimerExpire();
};
