// Copyrights JasonChoi(SEONG_CHAN) 2019

#include "Unreal_BattleTank/Public/Tank.h"
float ATank::GetHealthPercent() const
{
	return (float) m_iCurrentHealth / (float) m_iStartingHealth ;
}
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	m_iCurrentHealth = m_iStartingHealth;
}

float ATank::TakeDamage(float _fDamageAmount, struct FDamageEvent const & _DamageEvent, class AController * _EventInstigator, AActor * _DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(_fDamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, m_iCurrentHealth);

	m_iCurrentHealth -= DamageToApply;
	if (m_iCurrentHealth <= 0)
	{
		m_OnDeath.Broadcast();
	}
		
	return DamageToApply;
}