#include "silencedglock.h"

LINK_ENTITY_TO_CLASS(weapon_silencedglock, CSilencedGlock);

void CSilencedGlock::Spawn() {
    Precache();
    m_iId = WEAPON_SILENCED_GLOCK;
    SET_MODEL(ENT(pev), "models/w_silencedglock.mdl");

    m_iDefaultAmmo = GLOCK_DEFAULT_GIVE;

    FallInit(); // get ready to fall down.
}
void CSilencedGlock::Precache() { 
    PRECACHE_MODEL("models/v_silencedglock.mdl");
    PRECACHE_MODEL("models/w_silencedglock.mdl");
    PRECACHE_MODEL("models/p_silencedglock.mdl");

    m_iShell = PRECACHE_MODEL("models/shell.mdl"); // brass shell

    PRECACHE_SOUND("items/9mmclip1.wav");
    PRECACHE_SOUND("items/9mmclip2.wav");

    PRECACHE_SOUND("weapons/pl_gun1.wav"); //silenced handgun
    PRECACHE_SOUND("weapons/pl_gun2.wav"); //silenced handgun
    //PRECACHE_SOUND("weapons/pl_gun3.wav"); //handgun

    m_usFireGlock1 = PRECACHE_EVENT(1, "events/silencedglock1.sc");
    m_usFireGlock2 = PRECACHE_EVENT(1, "events/silencedglock2.sc");
}
bool CSilencedGlock::GetItemInfo(ItemInfo* p)
{
    p->pszName = STRING(pev->classname);
    p->pszAmmo1 = "9mm";
    p->iMaxAmmo1 = _9MM_MAX_CARRY;
    p->pszAmmo2 = NULL;
    p->iMaxAmmo2 = -1;
    p->iMaxClip = GLOCK_MAX_CLIP;
    p->iSlot = 1;
    p->iPosition = 2;
    p->iFlags = 0;
    p->iId = m_iId = WEAPON_SILENCED_GLOCK;
    p->iWeight = GLOCK_WEIGHT;

    return true;
}
bool CSilencedGlock::Deploy()
{
	// pev->body = 1;
	return DefaultDeploy("models/v_silencedglock.mdl", "models/p_silencedglock.mdl", GLOCK_DRAW, "onehanded");
}
void CSilencedGlock::SecondaryAttack()
{
	SilenceFire(0.1, 0.2, false);
}
void CSilencedGlock::PrimaryAttack()
{
	SilenceFire(0.01, 0.3, true);
}
void CSilencedGlock::SilenceFire(float flSpread, float flCycleTime, bool fUseAutoAim)
{
	if (m_iClip <= 0)
	{
		//if (m_fFireOnEmpty)
		{
			PlayEmptySound();
			m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(0.2);
		}

		return;
	}

	m_iClip--;

	m_pPlayer->pev->effects = (int)(m_pPlayer->pev->effects) | EF_MUZZLEFLASH;

	int flags;

#if defined(CLIENT_WEAPONS)
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	// player "shoot" animation
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	// silenced
	/*if (pev->body == 1)
	{
		m_pPlayer->m_iWeaponVolume = QUIET_GUN_VOLUME;
		m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;
	}
	else
	{
		// non-silenced*/
		m_pPlayer->m_iWeaponVolume = QUIET_GUN_VOLUME;
		m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;
	//}

	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecAiming;

	if (fUseAutoAim)
	{
		vecAiming = m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);
	}
	else
	{
		vecAiming = gpGlobals->v_forward;
	}

	Vector vecDir;
	vecDir = m_pPlayer->FireBulletsPlayer(1, vecSrc, vecAiming, Vector(flSpread, flSpread, flSpread), 8192, BULLET_PLAYER_9MM, 0, 0, m_pPlayer->pev, m_pPlayer->random_seed);

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), fUseAutoAim ? m_usFireGlock1 : m_usFireGlock2, 0.0, g_vecZero, g_vecZero, vecDir.x, vecDir.y, 0, 0, (m_iClip == 0) ? 1 : 0, 0);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (0 == m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		// HEV suit - indicate out of ammo condition
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", false, 0);

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 10, 15);
}
void CSilencedGlock::Reload()
{
	if (m_pPlayer->ammo_9mm <= 0)
		return;

	bool iResult;

	if (m_iClip == 0)
		iResult = DefaultReload(17, GLOCK_RELOAD, 1.5);
	else
		iResult = DefaultReload(17, GLOCK_RELOAD_NOT_EMPTY, 1.5);

	if (iResult)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 10, 15);
	}
}
void CSilencedGlock::WeaponIdle()
{
	ResetEmptySound();

	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	// only idle if the slid isn't back
	if (m_iClip != 0)
	{
		int iAnim;
		float flRand = UTIL_SharedRandomFloat(m_pPlayer->random_seed, 0.0, 1.0);

		if (flRand <= 0.3 + 0 * 0.75)
		{
			iAnim = GLOCK_IDLE3;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 49.0 / 16;
		}
		else if (flRand <= 0.6 + 0 * 0.875)
		{
			iAnim = GLOCK_IDLE1;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60.0 / 16.0;
		}
		else
		{
			iAnim = GLOCK_IDLE2;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 40.0 / 16.0;
		}
		SendWeaponAnim(iAnim);
	}
}
