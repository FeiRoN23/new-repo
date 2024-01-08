#include "ammodispenser.h"

LINK_ENTITY_TO_CLASS(ammo_dispenser, CAmmoDispenser)

void CAmmoDispenser::Spawn()
{
    pev->solid = SOLID_NOT;
    pev->movetype = MOVETYPE_NONE;
    ALERT(at_console, "Ammo dispenser spawned\n");
    //UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
}

void CAmmoDispenser::dispense_ammo() {
    ALERT(at_console, "dispensing 9mm ammo\n");
    //Create("item_sodacan", pev->origin, pev->angles, edict());
    edict_t* pent;
    pent = CREATE_NAMED_ENTITY(MAKE_STRING("ammo_9mmclip"));
    if (FNullEnt(pent))
    {
        ALERT(at_console, "NULL Ent in Create!\n");
        return;
    }
    CBaseEntity* ammoEntity = Instance(pent);
    
    ammoEntity->pev->origin = pev->origin;
    ammoEntity->pev->angles = pev->angles;
    ammoEntity->Spawn();
    ammoEntity->pev->movetype = MOVETYPE_NONE;
    ammoEntity->pev->solid = SOLID_TRIGGER;

    //Old method to spawn
    //Create("ammo_9mmclip", pev->origin, pev->angles, edict()); 
    
}

void CAmmoDispenser::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
    ALERT(at_console, "using dispenser targeting %s\n", STRING(pev->target));
    dispense_ammo();
}


