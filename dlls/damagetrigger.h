#include "extdll.h"
#include "util.h"
#include "cbase.h"


class CDamageTrigger:public CBaseEntity
{
public:
    void Spawn() override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
    void giveDamage(entvars_t* selfInflictor, float flDamage);
};