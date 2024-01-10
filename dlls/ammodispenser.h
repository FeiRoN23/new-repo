#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "weapons.h"

class CObjectDispenser:public CBaseEntity
{
public:
    void Spawn() override;
    void dispense_ammo(string_t ammoType);
};

class CButtonDispenser: public CBaseToggle
{
public:
    void Spawn() override;
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
    bool KeyValue(KeyValueData* pkvd) override;
    int m_spawnAmmoName;
    static const char* ammoTypesNames[];
    int ObjectCaps() override { return (CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | (pev->takedamage ? 0 : FCAP_IMPULSE_USE); }
};
