#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "weapons.h"

class CAmmoDispenser:public CBaseEntity
{
public:
    void Spawn() override;
    void dispense_ammo();
    void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
};
