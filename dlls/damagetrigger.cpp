#include "damagetrigger.h"

LINK_ENTITY_TO_CLASS(trigger_damage, CDamageTrigger);

void CDamageTrigger::Spawn()
{
    ALERT(at_console, "I SPAWNED, AGAIN !\n");
}


void CDamageTrigger::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
    ALERT(at_console, "message from use %s\n", STRING(pev->message));
    if(pActivator->IsPlayer())
    {
        ALERT(at_console, "damage value %g\n", pev->dmg);
        giveDamage(pActivator->pev, pev->dmg);
    }
}

void CDamageTrigger::giveDamage(entvars_t* selfInflictor, float flDamage)
{
    
    if(selfInflictor->takedamage != DAMAGE_NO)
    {
        selfInflictor->dmg_take += flDamage;
        selfInflictor->health -= flDamage;
        selfInflictor->dmg_save = flDamage;
        ALERT(at_console, "give damage ammount %g\n", flDamage);
    }
    if (selfInflictor->health <= 35)
    {
        selfInflictor->takedamage = DAMAGE_NO;
        ALERT(at_console, "No more damage given");
    }
    
    if (selfInflictor->health <= 0)
    {
        ALERT(at_console, "Killed");
        Killed(pev, GIB_NORMAL);
    }
}







