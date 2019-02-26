// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Projectile.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "ParticleDefinitions.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Unreal_BattleTank/Public/TankProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(m_CollisionMesh);
	m_CollisionMesh->SetNotifyRigidBodyCollision(true);
	m_CollisionMesh->SetVisibility(false);

	m_LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	
	m_LaunchBlast->SetupAttachment(m_CollisionMesh);

	m_TankProjectileMovementComponent = CreateDefaultSubobject<UTankProjectileMovementComponent>(FName("Projectile Movement"));
	m_TankProjectileMovementComponent->bAutoActivate = false;
}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float _fDeltaTime)
{
	Super::Tick(_fDeltaTime);

}


void AProjectile::LaunchProjectile(float _fSpeed)
{
	m_TankProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector* _fSpeed);
	m_TankProjectileMovementComponent->Activate();
}
