#include "ammodispenser.h"

LINK_ENTITY_TO_CLASS(ammo_dispenser, CAmmoDispenser)

void CAmmoDispenser::Spawn()
{
    ALERT(at_console, "Ammo dispenser spawned\n");
}

void CAmmoDispenser::dispense_ammo() {
    ALERT(at_console, "dispensing 9mm ammo\n");
    Create("ammo_9mmclip", pev->origin, pev->angles, edict());
}

void CAmmoDispenser::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
    ALERT(at_console, "using dispenser targeting %s\n", STRING(pev->target));
    dispense_ammo();
}


