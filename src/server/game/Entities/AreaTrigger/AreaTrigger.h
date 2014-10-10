/*
 * Copyright (C) 2012-2013 JadeCore <http://www.pandashan.com/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITYCORE_AREATRIGGER_H
#define TRINITYCORE_AREATRIGGER_H

#include "Object.h"

class Unit;
class SpellInfo;

class AreaTrigger : public WorldObject, public GridObject<AreaTrigger>
{
    public:
        AreaTrigger();
        ~AreaTrigger();

        void AddToWorld();
        void RemoveFromWorld();

        bool CreateAreaTrigger(uint32 guidlow, uint32 triggerEntry, Unit* caster, SpellInfo const* spell, Position const& pos);
        void Update(uint32 p_time);
        void Remove();
        uint32 GetSpellId() const { return GetUInt32Value(AREATRIGGER_FIELD_SPELL_ID); }
        int32 GetDuration() const { return _duration; }
        void SetDuration(int32 newDuration) { _duration = newDuration; }
        void Delay(int32 delaytime) { SetDuration(GetDuration() - delaytime); }
        Unit* GetCaster() const { return m_caster; }
        uint64 GetCasterGUID() const { return GetUInt64Value(AREATRIGGER_FIELD_CASTER); }
        void BindToCaster();
        void UnbindFromCaster();

        uint32 GetCreatedTime() const { return m_createdTime; }

        float GetVisualRadius() const { return m_visualRadius; }
        void SetVisualRadius(float radius) { m_visualRadius = radius; }

        uint32 GetCreationTimeMS() const { return m_CreationTimeMS; }

        bool IsAreaTriggerBox() const { return GetSpellId() == 140781; }

    protected:
        int32 _duration;
        uint32 m_CreationTimeMS;
        Unit* m_caster;
        float m_visualRadius;
        uint32 m_createdTime;
};
#endif