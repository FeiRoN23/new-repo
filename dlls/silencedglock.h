#pragma once
#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "weapons.h"
#include "player.h"

class CSilencedGlock: public CBasePlayerWeapon
{
public:
    void Spawn() override;
    void Precache() override;
    int iItemSlot() override { return 2; }
    bool GetItemInfo(ItemInfo* p) override;

    void PrimaryAttack() override;
    void SecondaryAttack() override;
    void SilenceFire(float flSpread, float flCycleTime, bool fUseAutoAim);
    bool Deploy() override;
    void Reload() override;
    void WeaponIdle() override;
    void Holster() override;

    bool UseDecrement() override
    {
#if defined(CLIENT_WEAPONS)
        return true;
#else
        return false;
#endif
    }

private:
    int m_iShell;
    
    unsigned short m_usFireGlock1;
    unsigned short m_usFireGlock2;
    
};
