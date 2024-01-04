#include "ammodispenser.h"

#include "weapons.h"
#include "../external/SDL2/begin_code.h"

LINK_ENTITY_TO_CLASS(ammo_dispenser, CAmmoDispenser)

void CAmmoDispenser::Think()
{
    
    ALERT(at_console, "Ammo dispenser next think variable at %g\n", m_nextThinkTime);
    if(m_nextThinkTime == 0)
    {
        m_nextThinkTime = 10.0f;
        ALERT(at_console, "my time is 0 setting 10 seconds\n");
        pev->nextthink = gpGlobals->time + m_nextThinkTime;
        
    } else {
        ALERT(at_console, "next time is %g\n", m_nextThinkTime);
        pev->nextthink = gpGlobals->time + m_nextThinkTime;
    }
    
    //Give_ammo_player();
    SpawnAmmo();
    
}

void CAmmoDispenser::Give_ammo_player()
{
    if(UTIL_GetLocalPlayer())
    {
        ALERT(at_console, "Found player now giving ammo\n");
        EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", 1, ATTN_NORM);
        UTIL_GetLocalPlayer()->GiveAmmo(AMMO_GLOCKCLIP_GIVE, "9mm", _9MM_MAX_CARRY);
    }
}

void CAmmoDispenser::SpawnAmmo()
{
    CBaseEntity* ammoEntity = UTIL_FindEntityByTargetname(NULL, "ammo_1");
    if(!ammoEntity) {
        if(UTIL_GetLocalPlayer()->ammo_9mm < 30)
        {
            ALERT(at_console, "spawning ammo\n");
            Create("ammo_9mmclip", pev->origin, pev->angles, edict());
        }
    }
    
}

void CAmmoDispenser::Spawn()
{
    ALERT(at_console, "Ammo dispenser spawned\n");
    pev->nextthink = gpGlobals->time;
}

bool CAmmoDispenser::KeyValue(KeyValueData* pkvd)
{
    if (FStrEq(pkvd->szKeyName, "mytime"))
    {
        m_nextThinkTime = atof(pkvd->szValue);
        return true;
    }
}


