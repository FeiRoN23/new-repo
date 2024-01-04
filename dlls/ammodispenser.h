#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CAmmoDispenser:public CBaseEntity
{
public:
    void Spawn() override;
    void Give_ammo_player();
    void Think() override;
    bool KeyValue(KeyValueData* pkvd) override;
    void SpawnAmmo();
private:
    float m_nextThinkTime;
};
