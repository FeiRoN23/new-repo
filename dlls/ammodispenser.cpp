#include "ammodispenser.h"

const char* CButtonDispenser::ammoTypesNames[] =
{
    "ammo_9mmclip",
    "ammo_9mmAR",
    "ammo_buckshot",
};

void CObjectDispenser::Spawn()
{
    pev->solid = SOLID_NOT;
    pev->movetype = MOVETYPE_NONE;
    ALERT(at_console, "Ammo dispenser spawned\n");
    
}

void CObjectDispenser::dispense_ammo(string_t ammoType) {
    ALERT(at_console, "dispensing %s\n", STRING(ammoType));
    edict_t* pent;
    pent = CREATE_NAMED_ENTITY(ammoType);
    
    if (FNullEnt(pent))
    {
        ALERT(at_console, "NULL Ent in Create!\n");
        return;
    }
    
    CBaseEntity* ammoEntity = Instance(pent);
    
    ammoEntity->pev->origin = Vector(pev->origin.x, pev->origin.y, pev->origin.z - 2.5f);
    ammoEntity->pev->angles = pev->angles;
    ammoEntity->Spawn();
    ammoEntity->pev->movetype = MOVETYPE_NONE;
    ammoEntity->pev->solid = SOLID_TRIGGER;
    
}

LINK_ENTITY_TO_CLASS(ammo_dispenser, CObjectDispenser)

void CButtonDispenser::Spawn()
{
    pev->movetype = MOVETYPE_PUSH;
    pev->solid = SOLID_BSP;
    SET_MODEL(ENT(pev), STRING(pev->model));
    SetUse(&CButtonDispenser::Use);
}


void CButtonDispenser::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
    if(pActivator->IsPlayer())
    {
        
        CBaseEntity* dispBaseEnt = UTIL_FindEntityByTargetname(nullptr, STRING(pev->target));
        
        if (dispBaseEnt)
        {
            auto dispenserEnt =  dynamic_cast<CObjectDispenser*>(dispBaseEnt);
            dispenserEnt->dispense_ammo(m_spawnAmmoName);
        }
        
    }
    
}

bool CButtonDispenser::KeyValue(KeyValueData* pkvd)
{
    if (FStrEq(pkvd->szKeyName, "ammoSpawn"))
    {
        int object = atoi(pkvd->szValue);
        if (object >= 0 && object < ARRAYSIZE(ammoTypesNames))
            m_spawnAmmoName = MAKE_STRING(ammoTypesNames[object]);
        return true;
    }
}


LINK_ENTITY_TO_CLASS(func_button_dispenser, CButtonDispenser);



