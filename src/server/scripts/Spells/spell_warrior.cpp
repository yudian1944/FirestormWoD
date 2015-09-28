/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

/*
 * Scripts for spells with SPELLFAMILY_WARRIOR and SPELLFAMILY_GENERIC spells used by warrior players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warr_".
 */

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "GridNotifiers.h"

enum WarriorSpells
{
    WARRIOR_SPELL_DEEP_WOUNDS                   = 115767,
    WARRIOR_SPELL_SHOCKWAVE_STUN                = 132168,
    WARRIOR_SPELL_RALLYING_CRY                  = 97463,
    WARRIOR_SPELL_GLYPH_OF_MORTAL_STRIKE        = 58368,
    WARRIOR_SPELL_SWORD_AND_BOARD               = 50227,
    WARRIOR_SPELL_SHIELD_SLAM                   = 23922,
    WARRIOR_SPELL_ALLOW_RAGING_BLOW             = 131116,
    WARRIOR_SPELL_MOCKING_BANNER_TAUNT          = 114198,
    WARRIOR_NPC_MOCKING_BANNER                  = 59390,
    WARRIOR_SPELL_ENRAGE                        = 12880,
    WARRIOR_SPELL_COLOSSUS_SMASH                = 167105,
    WARRIOR_SPELL_MORTAL_STRIKE_AURA            = 12294,
    WARRIOR_SPELL_TASTE_FOR_BLOOD               = 56636,
    WARRIOR_SPELL_ALLOW_OVERPOWER               = 60503,
    WARRIOR_SPELL_SECOND_WIND_REGEN             = 16491,
    WARRIOR_SPELL_DRAGON_ROAR_KNOCK_BACK        = 118895,
    WARRIOR_SPELL_PHYSICAL_VULNERABILITY        = 81326,
    WARRIOR_SPELL_SHIELD_BLOCK_TRIGGERED        = 132404,
    WARRIOR_SPELL_GLYPH_OF_HINDERING_STRIKES    = 58366,
    WARRIOR_SPELL_SLUGGISH                      = 129923,
    WARRIOR_SPELL_IMPENDING_VICTORY             = 103840,
    WARRIOR_SPELL_GLYPH_OF_COLOSSUS_SMASH       = 89003,
    WARRIOR_SPELL_SUNDER_ARMOR                  = 7386,
    WARRIOR_SPELL_SHIELD_OF_WALL_NOSHIELD       = 146128,
    WARRIOR_SPELL_SHIELD_OF_WALL_HORDE          = 146127,
    WARRIOR_SPELL_SHIELD_OF_WALL_ALLIANCE       = 147925,
    WARRIOR_SPELL_SPELL_REFLECTION_NOSHIELD     = 146120,
    WARRIOR_SPELL_SPELL_REFLECTION_HORDE        = 146122,
    WARRIOR_SPELL_SPELL_REFLECTION_ALLIANCE     = 147923,
    WARRIOR_SPELL_GAG_ORDER_SILENCE             = 18498,
    WARRIOR_SPELL_DOUBLE_TIME_MARKER            = 124184,
    WARRIOR_ENHANCED_WHIRLWIND                  = 157473,
    WARROR_MEAT_CLEAVER_TARGET_MODIFIER         = 85739,
    WARRIOR_HEAVY_REPERCUSSIONS                 = 169680
};

/// Ravager - 152277
class spell_warr_ravager : public SpellScriptLoader
{
    public:
        spell_warr_ravager() : SpellScriptLoader("spell_warr_ravager") { }

        class spell_warr_ravager_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_ravager_AuraScript);

            enum eDatas
            {
                RavagerNPC    = 76168,

                RavagerDamage = 156287
            };

            void CalculateParryPCT(constAuraEffectPtr p_AurEff, int32& p_Amount, bool& p_CanBeRecalculated)
            {
                if (GetCaster() == nullptr)
                    return;

                if (Player* l_Player = GetCaster()->ToPlayer())
                {
                    if (l_Player->GetSpecializationId(l_Player->GetActiveSpec()) != SpecIndex::SPEC_WARRIOR_PROTECTION)
                        p_Amount = 0;
                }
            }

            void OnTick(constAuraEffectPtr p_AurEff)
            {
                if (Unit* l_Caster = GetCaster())
                {
                    Creature* l_Ravager = nullptr;
                    for (auto l_Iter : l_Caster->m_Controlled)
                    {
                        if (l_Iter->GetEntry() == eDatas::RavagerNPC)
                            l_Ravager = l_Iter->ToCreature();
                    }

                    if (l_Ravager == nullptr)
                        return;

                    l_Caster->CastSpell(l_Ravager, eDatas::RavagerDamage, true);
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_ravager_AuraScript::CalculateParryPCT, EFFECT_0, SPELL_AURA_MOD_PARRY_PERCENT);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warr_ravager_AuraScript::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_ravager_AuraScript();
        }
};

/// Victorious State - 32216
class spell_warr_victorious_state: public SpellScriptLoader
{
    public:
        spell_warr_victorious_state() : SpellScriptLoader("spell_warr_victorious_state") { }

        class spell_warr_victorious_state_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_victorious_state_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasSpellCooldown(WARRIOR_SPELL_IMPENDING_VICTORY))
                        _player->RemoveSpellCooldown(WARRIOR_SPELL_IMPENDING_VICTORY, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_victorious_state_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_victorious_state_SpellScript();
        }
};

/// Called by Heroic Strike - 78 and Cleave - 845
/// Glyph of Hindering Strikes - 58366
class spell_warr_glyph_of_hindering_strikes: public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_hindering_strikes() : SpellScriptLoader("spell_warr_glyph_of_hindering_strikes") { }

        class spell_warr_glyph_of_hindering_strikes_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_glyph_of_hindering_strikes_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (_player->HasAura(WARRIOR_SPELL_GLYPH_OF_HINDERING_STRIKES))
                            _player->CastSpell(target, WARRIOR_SPELL_SLUGGISH, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_glyph_of_hindering_strikes_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_glyph_of_hindering_strikes_SpellScript();
        }
};

/// Shield Block - 2565
class spell_warr_shield_block: public SpellScriptLoader
{
    public:
        spell_warr_shield_block() : SpellScriptLoader("spell_warr_shield_block") { }

        class spell_warr_shield_block_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_shield_block_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                    caster->CastSpell(caster, WARRIOR_SPELL_SHIELD_BLOCK_TRIGGERED, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_shield_block_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_shield_block_SpellScript();
        }
};

/// Storm Bolt - 107570, Storm Bolt (Off Hand) - 145585
class spell_warr_storm_bolt: public SpellScriptLoader
{
    public:
        spell_warr_storm_bolt() : SpellScriptLoader("spell_warr_storm_bolt") { }

        class spell_warr_storm_bolt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_storm_bolt_SpellScript);

            enum eSpells
            {
                StormBoltOffHand = 107570,
                StormBoltStun = 132169
            };

            void HandleOnCast()
            {
                Unit* l_Caster = GetCaster();
                Unit* l_Target = GetExplTargetUnit();

                if (l_Target == nullptr)
                    return;

                if (GetSpellInfo()->Id == eSpells::StormBoltOffHand && !l_Target->IsImmunedToSpellEffect(sSpellMgr->GetSpellInfo(eSpells::StormBoltStun), EFFECT_0))
                    l_Caster->CastSpell(l_Target, eSpells::StormBoltStun, true);
            }

            void HandleOnHit()
            {
                if (Unit* l_Target = GetHitUnit())
                {
                    if (l_Target->IsImmunedToSpellEffect(sSpellMgr->GetSpellInfo(eSpells::StormBoltStun), EFFECT_0))
                        SetHitDamage(GetHitDamage() * 4); ///< Deals quadruple damage to targets permanently immune to stuns
                }
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_warr_storm_bolt_SpellScript::HandleOnCast);
                OnHit += SpellHitFn(spell_warr_storm_bolt_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_storm_bolt_SpellScript();
        }
};

enum ColossusSpells
{
    SPELL_WARRIOR_WEAPONS_MASTER = 76838,
};

/// Colossus Smash - 167105
class spell_warr_colossus_smash: public SpellScriptLoader
{
    public:
        spell_warr_colossus_smash() : SpellScriptLoader("spell_warr_colossus_smash") { }

        class spell_warr_colossus_smash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_colossus_smash_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        caster->CastSpell(target, WARRIOR_SPELL_PHYSICAL_VULNERABILITY, true);

                        if (caster->HasAura(WARRIOR_SPELL_GLYPH_OF_COLOSSUS_SMASH))
                            caster->CastSpell(target, WARRIOR_SPELL_SUNDER_ARMOR, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_colossus_smash_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_colossus_smash_SpellScript();
        }
};

/// Dragon Roar - 118000
class spell_warr_dragon_roar: public SpellScriptLoader
{
    public:
        spell_warr_dragon_roar() : SpellScriptLoader("spell_warr_dragon_roar") { }

        class spell_warr_dragon_roar_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_dragon_roar_SpellScript);

            void HandleAfterHit()
            {
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetHitUnit())
                        caster->CastSpell(target, WARRIOR_SPELL_DRAGON_ROAR_KNOCK_BACK, true);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warr_dragon_roar_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_dragon_roar_SpellScript();
        }
};

/// Staggering Shout - 107566
class spell_warr_staggering_shout: public SpellScriptLoader
{
    public:
        spell_warr_staggering_shout() : SpellScriptLoader("spell_warr_staggering_shout") { }

        class spell_warr_staggering_shout_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_staggering_shout_SpellScript);

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(JadeCore::UnitAuraTypeCheck(false, SPELL_AURA_MOD_DECREASE_SPEED));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_staggering_shout_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_staggering_shout_SpellScript();
        }
};

/// Second Wind - 29838
class spell_warr_second_wind: public SpellScriptLoader
{
    public:
        spell_warr_second_wind() : SpellScriptLoader("spell_warr_second_wind") { }

        class spell_warr_second_wind_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_second_wind_AuraScript);

            void OnProc(constAuraEffectPtr p_AurEff, ProcEventInfo& l_ProcInfo)
            {
                PreventDefaultAction();

                if (Unit* l_Caster = GetCaster())
                {
                    if (l_Caster->GetHealthPct() < 35.0f && !l_Caster->HasAura(WARRIOR_SPELL_SECOND_WIND_REGEN))
                        l_Caster->CastSpell(l_Caster, WARRIOR_SPELL_SECOND_WIND_REGEN, true);
                }
            }

            void OnRemove(constAuraEffectPtr p_AurEff, AuraEffectHandleModes /*p_Mode*/)
            {
                if (Unit* l_Caster = GetCaster())
                {
                    if (l_Caster->HasAura(WARRIOR_SPELL_SECOND_WIND_REGEN))
                        l_Caster->RemoveAura(WARRIOR_SPELL_SECOND_WIND_REGEN);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_second_wind_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectProc += AuraEffectProcFn(spell_warr_second_wind_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_second_wind_AuraScript();
        }
};

/// Second Wind (aura) - 29838
class PlayerScript_second_wind : public PlayerScript
{
public:
    PlayerScript_second_wind() :PlayerScript("PlayerScript_second_wind") {}

    void OnModifyHealth(Player * p_Player, int32 p_Value)
    {
        if (p_Player->getClass() == CLASS_WARRIOR && p_Player->HasAura(WARRIOR_SPELL_SECOND_WIND_REGEN))
        {
            /// Remove aura if player has more than 35% life
            if (p_Player->GetHealthPct() >= 35.0f)
                p_Player->RemoveAura(WARRIOR_SPELL_SECOND_WIND_REGEN);
        }
    }
};

/// last update : 6.1.2 19802
/// Berzerker Rage - 18499
class spell_warr_berzerker_rage: public SpellScriptLoader
{
    public:
        spell_warr_berzerker_rage() : SpellScriptLoader("spell_warr_berzerker_rage") { }

        class spell_warr_berzerker_rage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_berzerker_rage_SpellScript);

            void HandleOnHit()
            {
                if (Player* l_Player = GetCaster()->ToPlayer())
                {
                    if (l_Player->GetSpecializationId(l_Player->GetActiveSpec()) != SPEC_WARRIOR_ARMS)
                        l_Player->CastSpell(l_Player, WARRIOR_SPELL_ENRAGE, true); ///< It should proc only on fury and prot because they have Enrage passive talent and arms not
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_berzerker_rage_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_berzerker_rage_SpellScript();
        }
};

/// Enrage - 12880
class spell_warr_enrage: public SpellScriptLoader
{
    public:
        spell_warr_enrage() : SpellScriptLoader("spell_warr_enrage") { }

        class spell_warr_enrage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_enrage_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARRIOR_FURY && _player->getLevel() >= GetSpellInfo()->BaseLevel)
                        _player->AddAura(WARRIOR_SPELL_ALLOW_RAGING_BLOW, _player);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_enrage_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_enrage_SpellScript();
        }
};

/// Mocking Banner - 114192
class spell_warr_mocking_banner: public SpellScriptLoader
{
    public:
        spell_warr_mocking_banner() : SpellScriptLoader("spell_warr_mocking_banner") { }

        class spell_warr_mocking_banner_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_mocking_banner_AuraScript);

            enum eDatas
            {
                NPCMockingBanner = 59390,
                MockingBannerTaunt = 114198
            };

            void OnTick(constAuraEffectPtr /*p_AurEff*/)
            {
                Unit* l_Target = GetTarget();

                std::list<Creature*> l_BannerList;
                std::list<Creature*> l_TempList;

                l_Target->GetCreatureListWithEntryInGrid(l_TempList, eDatas::NPCMockingBanner, GetSpellInfo()->RangeEntry->maxRangeHostile);

                l_BannerList = l_TempList;

                // Remove other players banners
                for (auto itr : l_TempList)
                {
                    Unit* l_Owner = itr->GetOwner();
                    if (l_Owner && l_Owner->GetGUID() == l_Target->GetGUID() && itr->isSummon())
                        continue;

                    l_BannerList.remove(itr);
                }

                for (auto itr : l_BannerList)
                    l_Target->CastSpell(itr, eDatas::MockingBannerTaunt, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warr_mocking_banner_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_mocking_banner_AuraScript();
        }
};

/// Raging Blow - 85288
class spell_warr_raging_blow: public SpellScriptLoader
{
    public:
        spell_warr_raging_blow() : SpellScriptLoader("spell_warr_raging_blow") { }

        class spell_warr_raging_blow_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_raging_blow_SpellScript);

            enum eSpells
            {
                MeatCleaverTargetModifier = 85739
            };

            void HandleAfterCast()
            {
                if (Unit* l_Caster = GetCaster())
                {
                    if (AuraPtr ragingBlow = l_Caster->GetAura(WARRIOR_SPELL_ALLOW_RAGING_BLOW))
                        ragingBlow->ModStackAmount(-1);

                    if (l_Caster->HasAura(eSpells::MeatCleaverTargetModifier))
                        l_Caster->RemoveAura(eSpells::MeatCleaverTargetModifier);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warr_raging_blow_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_raging_blow_SpellScript();
        }
};

/// last update : 6.1.2 19802
/// Devastate - 20243
class spell_warr_devaste: public SpellScriptLoader
{
    public:
        spell_warr_devaste() : SpellScriptLoader("spell_warr_devaste") { }

        class spell_warr_devaste_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_devaste_SpellScript);

            enum eSpells
            {
                UnyieldingStrikesAura = 169685,
                UnyieldingStrikesProc = 169686,
                SwordandBoard = 46953
            };

            void HandleOnHit()
            {
                Player* l_Player = GetCaster()->ToPlayer();

                if (l_Player == nullptr)
                    return;

                const SpellInfo* l_SpellInfo = sSpellMgr->GetSpellInfo(eSpells::SwordandBoard);

                if (l_SpellInfo && l_Player->HasAura(eSpells::SwordandBoard) && roll_chance_i(l_SpellInfo->Effects[EFFECT_0].BasePoints))
                {
                    l_Player->CastSpell(l_Player, WARRIOR_SPELL_SWORD_AND_BOARD, true);
                    l_Player->RemoveSpellCooldown(WARRIOR_SPELL_SHIELD_SLAM, true);
                }

                if (l_Player->HasAura(eSpells::UnyieldingStrikesAura))
                    l_Player->CastSpell(l_Player, eSpells::UnyieldingStrikesProc, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_devaste_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_devaste_SpellScript();
        }
};

/// Mortal strike - 12294
class spell_warr_mortal_strike: public SpellScriptLoader
{
    public:
        spell_warr_mortal_strike() : SpellScriptLoader("spell_warr_mortal_strike") { }

        class spell_warr_mortal_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_mortal_strike_SpellScript);

            void HandleOnHit()
            {
                /// Fix Apply Mortal strike buff on player only if he has the correct glyph
                if (Unit* l_Caster = GetCaster())
                {
                    if (l_Caster->HasAura(WARRIOR_SPELL_MORTAL_STRIKE_AURA) && !l_Caster->HasAura(WARRIOR_SPELL_GLYPH_OF_MORTAL_STRIKE))
                        l_Caster->RemoveAura(WARRIOR_SPELL_MORTAL_STRIKE_AURA);

                    if (l_Caster->HasAura(WARRIOR_SPELL_TASTE_FOR_BLOOD))
                    {
                        l_Caster->AddComboPoints(1);
                        l_Caster->StartReactiveTimer(REACTIVE_OVERPOWER);
                        l_Caster->CastSpell(l_Caster, WARRIOR_SPELL_ALLOW_OVERPOWER, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_mortal_strike_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_mortal_strike_SpellScript();
        }
};

/// last update : 6.1.2 19802
/// Mortal strike - 12294, Wild Strike - 100130
class spell_warr_glyph_of_die_by_the_sword : public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_die_by_the_sword() : SpellScriptLoader("spell_warr_glyph_of_die_by_the_sword") { }

        class spell_warr_glyph_of_die_by_the_sword_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_glyph_of_die_by_the_sword_SpellScript);

            enum eSpells
            {
                MortalStrike = 12294,
                WildStrike = 100130,
                GlyphofDiebytheSword = 58386,
                DiebytheSword = 118038
            };

            void HandleOnHit()
            {
                Unit* l_Caster = GetCaster();

                if (!l_Caster->HasAura(eSpells::GlyphofDiebytheSword))
                    return;

                const SpellInfo* l_SpellInfo = sSpellMgr->GetSpellInfo(eSpells::GlyphofDiebytheSword);

                if (l_SpellInfo == nullptr)
                    return;

                if (AuraPtr l_DieByTheSword = l_Caster->GetAura(eSpells::DiebytheSword))
                {
                    switch (GetSpellInfo()->Id)
                    {
                    case eSpells::MortalStrike: ///< increases its duration by 2 sec
                        l_DieByTheSword->SetDuration(l_DieByTheSword->GetDuration() + (l_SpellInfo->Effects[EFFECT_1].BasePoints * IN_MILLISECONDS));
                    case eSpells::WildStrike: ///< increases its duration by 0.25 sec
                        l_DieByTheSword->SetDuration(l_DieByTheSword->GetDuration() + (((float)l_SpellInfo->Effects[EFFECT_0].BasePoints / 4) * IN_MILLISECONDS));
                        break;
                    default:
                        break;
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_glyph_of_die_by_the_sword_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_glyph_of_die_by_the_sword_SpellScript();
        }
};

/// Rallying cry - 97462
class spell_warr_rallying_cry: public SpellScriptLoader
{
    public:
        spell_warr_rallying_cry() : SpellScriptLoader("spell_warr_rallying_cry") { }

        class spell_warr_rallying_cry_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_rallying_cry_SpellScript);
            
            enum eSpells
            {
                GLYPH_OF_RALLYING_CRY = 159754,
                GLYPH_OF_RALLYING_CRY_BUFF = 159756
            };

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* l_Player = GetCaster()->ToPlayer())
                {
                    int32 l_Bp0 = 0;
                    std::list<Unit*> l_MemberList;

                    l_Player->GetRaidMembers(l_MemberList);

                    for (auto l_Itr : l_MemberList)
                    {
                        if (l_Itr->IsWithinDistInMap(l_Player, GetSpellInfo()->Effects[EFFECT_0].RadiusEntry->radiusFriend))
                        {
                            l_Bp0 = CalculatePct(l_Itr->GetMaxHealth(), GetSpellInfo()->Effects[EFFECT_0].BasePoints);
                            l_Player->CastCustomSpell(l_Itr, WARRIOR_SPELL_RALLYING_CRY, &l_Bp0, NULL, NULL, true);
                        }
                    }

                    l_Bp0 = CalculatePct(l_Player->GetMaxHealth(), GetSpellInfo()->Effects[EFFECT_0].BasePoints);
                    l_Player->CastCustomSpell(l_Player, WARRIOR_SPELL_RALLYING_CRY, &l_Bp0, NULL, NULL, true);

                    /// Glyph of Rallying Cry
                    if (l_Player->HasAura(GLYPH_OF_RALLYING_CRY))
                        l_Player->CastSpell(l_Player, GLYPH_OF_RALLYING_CRY_BUFF, true);
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_warr_rallying_cry_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_rallying_cry_SpellScript();
        }
};

/// Heroic leap - 6544
class spell_warr_heroic_leap: public SpellScriptLoader
{
    public:
        spell_warr_heroic_leap() : SpellScriptLoader("spell_warr_heroic_leap") { }

        class spell_warr_heroic_leap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_heroic_leap_SpellScript);

            enum eSpells
            {
                HeroicLeapJump         = 94954
            };

            SpellCastResult CheckElevation()
            {
                Player* l_Player = GetCaster()->ToPlayer();
                WorldLocation* l_SpellDest = const_cast<WorldLocation*>(GetExplTargetDest());

                if (!l_Player || !l_SpellDest)
                    return SPELL_FAILED_DONT_REPORT;

                if (l_SpellDest->GetPositionZ() > l_Player->GetPositionZ() + 5.0f)
                    return SPELL_FAILED_NOPATH;
                else if (l_Player->HasAuraType(SPELL_AURA_MOD_ROOT) || l_Player->HasAuraType(SPELL_AURA_MOD_ROOT_2))
                    return SPELL_FAILED_ROOTED;
                else if (l_Player->GetMap()->IsBattlegroundOrArena())
                {
                    if (Battleground* l_Bg = l_Player->GetBattleground())
                    {
                        if (l_Bg->GetStatus() != STATUS_IN_PROGRESS)
                            return SPELL_FAILED_NOT_READY;
                    }
                }

                return SPELL_CAST_OK;
            }

            void HandleOnCast()
            {
                WorldLocation* l_SpellDest = const_cast<WorldLocation*>(GetExplTargetDest());
                if (l_SpellDest)
                    GetCaster()->CastSpell(l_SpellDest->GetPositionX(), l_SpellDest->GetPositionY(), l_SpellDest->GetPositionZ(), eSpells::HeroicLeapJump, true);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warr_heroic_leap_SpellScript::CheckElevation);
                OnCast += SpellCastFn(spell_warr_heroic_leap_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_heroic_leap_SpellScript();
        }
};

/// Heroic Leap (damage) - 52174
class spell_warr_heroic_leap_damage: public SpellScriptLoader
{
    public:
        spell_warr_heroic_leap_damage() : SpellScriptLoader("spell_warr_heroic_leap_damage") { }

        class spell_warr_heroic_leap_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_heroic_leap_damage_SpellScript);

            enum eSpells
            {
                Taunt                  = 355,
                HeroicLeapJump         = 94954,
                SpellPvp4PBonus        = 133277,
                GlyphOfHeroicLeapSpeed = 133278,
                ImprovedHeroicLeap     = 157449,
                GlyphOfHeroicLeap      = 159708
            };

            void HandleAfterCast()
            {
                Unit* l_Caster = GetCaster();

                if (l_Caster->HasAura(eSpells::GlyphOfHeroicLeap) || l_Caster->HasAura(eSpells::SpellPvp4PBonus))
                    l_Caster->CastSpell(l_Caster, eSpells::GlyphOfHeroicLeapSpeed, true);

                Player* l_Player = l_Caster->ToPlayer();
                if (!l_Player)
                    return;

                if (l_Player->HasAura(eSpells::ImprovedHeroicLeap) && l_Player->HasSpellCooldown(eSpells::Taunt))
                    l_Player->RemoveSpellCooldown(eSpells::Taunt, true);
            }

            void HandleOnHit()
            {
                Player* l_Player = GetCaster()->ToPlayer();
                if (!l_Player)
                    return;

                if (l_Player->GetSpecializationId(l_Player->GetActiveSpec()) == SPEC_WARRIOR_FURY)
                    SetHitDamage(int32(GetHitDamage() * 1.2f));
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warr_heroic_leap_damage_SpellScript::HandleAfterCast);
                OnHit += SpellHitFn(spell_warr_heroic_leap_damage_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_heroic_leap_damage_SpellScript();
        }
};

enum class ShockwaveValues : uint32
{
    SpellId = 46968
};

/// Shockwave - 46968
class spell_warr_shockwave: public SpellScriptLoader
{
    public:
        spell_warr_shockwave() : SpellScriptLoader("spell_warr_shockwave") { }

        class spell_warr_shockwave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_shockwave_SpellScript);

            void HandleDamage(SpellEffIndex effIndex)
            {
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetHitUnit())
                        caster->CastSpell(target, WARRIOR_SPELL_SHOCKWAVE_STUN, true);
            }

            /// Cooldown reduced by 20 sec if it strikes at least 3 targets.
            void HandleAfterHit()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return;

                if (int32(GetSpell()->GetUnitTargetCount()) >= GetSpellInfo()->Effects[EFFECT_0].BasePoints)
                    GetCaster()->ToPlayer()->ReduceSpellCooldown((uint32)ShockwaveValues::SpellId, GetSpellInfo()->Effects[EFFECT_3].BasePoints * IN_MILLISECONDS);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_shockwave_SpellScript::HandleDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
                AfterCast += SpellCastFn(spell_warr_shockwave_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_shockwave_SpellScript();
        }
};

/// Glyph of Raging Blow - 159740
class spell_warr_glyph_of_raging_blow: public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_raging_blow() : SpellScriptLoader("spell_warr_glyph_of_raging_blow") { }

        class spell_warr_glyph_of_raging_blow_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_glyph_of_raging_blow_AuraScript);

            enum eSpells
            {
                RagingBlow = 96103,
                RagingBlowOffHand = 85384
            };

            void OnProc(constAuraEffectPtr p_AurEff, ProcEventInfo& p_ProcEventInfo)
            {
                PreventDefaultAction();

                Unit* l_Caster = GetCaster();
                if (!l_Caster)
                    return;

                SpellInfo const* l_TriggeredBySpell = p_ProcEventInfo.GetDamageInfo()->GetSpellInfo();
                if (!l_TriggeredBySpell)
                    return;

                /// Should proc when Raging Blow (main hand and offhand)...
                if (l_TriggeredBySpell->Id != eSpells::RagingBlow)
                    return;

                /// ...are both critical
                if (!(p_ProcEventInfo.GetHitMask() & PROC_EX_CRITICAL_HIT))
                    return;

                l_Caster->CastSpell(l_Caster, p_AurEff->GetTriggerSpell(), true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warr_glyph_of_raging_blow_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_glyph_of_raging_blow_AuraScript();
        }
};


/// Bloodthirst - 23881
class spell_warr_bloodthirst: public SpellScriptLoader
{
    public:
        spell_warr_bloodthirst() : SpellScriptLoader("spell_warr_bloodthirst") { }

        class spell_warr_bloodthirst_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_bloodthirst_SpellScript);

            enum eSpells
            {
                Bloodthirst     = 23881,
                BloodthirstHeal = 117313,
                Bloodsurge      = 46915,
                BloodsurgeProc  = 46916,
            };

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(eSpells::Bloodthirst) || !sSpellMgr->GetSpellInfo(eSpells::BloodthirstHeal))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                Unit* l_Caster = GetCaster();

                if (GetHitDamage())
                {
                    l_Caster->CastSpell(l_Caster, eSpells::BloodthirstHeal, true);

                    if (AuraEffectPtr l_Bloodsurge = l_Caster->GetAuraEffect(eSpells::Bloodsurge, EFFECT_0))
                        if (roll_chance_i(l_Bloodsurge->GetAmount()))
                            l_Caster->CastSpell(l_Caster, eSpells::BloodsurgeProc, true);
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_bloodthirst_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_bloodthirst_SpellScript();
        }
};

/// Bloodthirst (heal) - 117313
class spell_warr_bloodthirst_heal: public SpellScriptLoader
{
    public:
        spell_warr_bloodthirst_heal() : SpellScriptLoader("spell_warr_bloodthirst_heal") { }

        class spell_warr_bloodthirst_heal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_bloodthirst_heal_SpellScript);

            enum eSpells
            {
                GlyphOfRagingBlowHealMod = 159747
            };

            void HandleHeal()
            {
                Unit* l_Caster = GetCaster();
                int32 l_Heal = GetHitHeal();

                if (AuraEffectPtr l_GlyphOfRagingBlow = l_Caster->GetAuraEffect(eSpells::GlyphOfRagingBlowHealMod, EFFECT_0))
                {
                    AddPct(l_Heal, l_GlyphOfRagingBlow->GetBaseAmount());
                    l_GlyphOfRagingBlow->GetBase()->Remove();
                }

                SetHitHeal(l_Heal);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_bloodthirst_heal_SpellScript::HandleHeal);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_bloodthirst_heal_SpellScript;
        }
};


/// Victory Rush - 34428
class spell_warr_victory_rush: public SpellScriptLoader
{
    public:
        spell_warr_victory_rush() : SpellScriptLoader("spell_warr_victory_rush") { }

        class spell_warr_victory_rush_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_victory_rush_SpellScript);

            enum eSpells
            {
                VictoriousState   = 32216,
                VictoryRushDamage = 34428,
                VictoryRushHeal   = 118779
            };

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(eSpells::VictoryRushDamage))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                if (!GetHitUnit())
                    return;

                if (Unit* caster = GetCaster())
                {
                    caster->CastSpell(caster, eSpells::VictoryRushHeal, true);

                    if (caster->HasAura(eSpells::VictoriousState))
                        caster->RemoveAura(eSpells::VictoriousState);
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_victory_rush_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_victory_rush_SpellScript();
        }
};

/// Victory Rush (heal) - 118779
class spell_warr_victory_rush_heal: public SpellScriptLoader
{
    public:
        spell_warr_victory_rush_heal() : SpellScriptLoader("spell_warr_victory_rush_heal") { }

        class spell_warr_victory_rush_heal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_victory_rush_heal_SpellScript);

            enum eSpells
            {
                GlyphOfVictoryRush = 58382
            };

            void HandleHeal()
            {
                Unit* l_Caster = GetCaster();
                int32 l_Heal = GetHitHeal();

                if (AuraEffectPtr l_GlyphOfVictoryRush = l_Caster->GetAuraEffect(eSpells::GlyphOfVictoryRush, EFFECT_0))
                    AddPct(l_Heal, l_GlyphOfVictoryRush->GetAmount());

                SetHitHeal(l_Heal);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_victory_rush_heal_SpellScript::HandleHeal);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_victory_rush_heal_SpellScript;
        }
};

/// Called By Thunder Clap - 6343, Mortal Strike - 12294, Bloodthirst - 23881 and Devastate - 20243
/// Deep Wounds - 115767
class spell_warr_deep_wounds: public SpellScriptLoader
{
    public:
        spell_warr_deep_wounds() : SpellScriptLoader("spell_warr_deep_wounds") { }

        class spell_warr_deep_wounds_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_deep_wounds_SpellScript);

            void HandleOnHit()
            {
                Unit* l_Caster = GetCaster();
                Unit* l_Target = GetHitUnit();
                if (!l_Target)
                    return;

                if (l_Caster->GetTypeId() == TYPEID_PLAYER && l_Caster->ToPlayer()->GetSpecializationId(l_Caster->ToPlayer()->GetActiveSpec()) != SPEC_WARRIOR_PROTECTION)
                    return;

                if (l_Target->GetGUID() == l_Caster->GetGUID())
                    return;

                if (l_Caster->getLevel() >= GetSpellInfo()->BaseLevel)
                    l_Caster->CastSpell(l_Target, WARRIOR_SPELL_DEEP_WOUNDS, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_deep_wounds_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_deep_wounds_SpellScript();
        }
};

enum ChargeSpells
{
    SPELL_WARR_WARBRINGER_STUN    = 7922,
    SPELL_WARR_GLYPH_OF_BULL_RUSH = 94372,
    SPELL_WARR_DOUBLE_TIME        = 103827,
    SPELL_WARR_WARBRINGER         = 103828,
    SPELL_WARR_CHARGE_ROOT        = 105771,
    SPELL_WARR_DOUBLE_TIME_MARKER = 124184,
    SPELL_WOD_PVP_FURY_2P         = 165639,
    SPELL_WOD_PVP_FURY_2P_EFFECT  = 165640,
    SPELL_WOD_PVP_ARMS_2P         = 165636,
    SPELL_WOD_PVP_ARMS_2P_EFFECT  = 165638,
    SPELL_WOD_PVP_PROT_2P         = 165641,
    SPELL_WOD_PVP_PROT_2P_EFFECT  = 165642
};

/// Charge - 100
class spell_warr_charge: public SpellScriptLoader
{
    public:
        spell_warr_charge() : SpellScriptLoader("spell_warr_charge") { }

    class spell_warr_charge_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_charge_SpellScript)

        bool m_HasAuraDoubleTimeMarker = false;

        void HandleOnCast()
        {
            if (Unit* l_Caster = GetCaster())
            {
                if (l_Caster->HasAura(WARRIOR_SPELL_DOUBLE_TIME_MARKER))
                    m_HasAuraDoubleTimeMarker = true;

                /// Warrior WoD PvP 2P bonuses
                if (l_Caster->getLevel() == 100)
                {
                    switch (l_Caster->ToPlayer()->GetSpecializationId())
                    {
                        case SPEC_WARRIOR_FURY:
                        {
                            if (l_Caster->HasAura(SPELL_WOD_PVP_FURY_2P))
                                l_Caster->CastSpell(l_Caster, SPELL_WOD_PVP_FURY_2P_EFFECT, true);
                            break;
                        }
                        case SPEC_WARRIOR_ARMS:
                        {
                            if (l_Caster->HasAura(SPELL_WOD_PVP_ARMS_2P))
                                l_Caster->CastSpell(l_Caster, SPELL_WOD_PVP_ARMS_2P_EFFECT, true);
                            break;
                        }
                        case SPEC_WARRIOR_PROTECTION:
                        {
                            if (l_Caster->HasAura(SPELL_WOD_PVP_PROT_2P))
                                l_Caster->CastSpell(l_Caster, SPELL_WOD_PVP_PROT_2P_EFFECT, true);
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }

        void HandleCharge(SpellEffIndex /*effIndex*/)
        {
            Unit* l_Caster = GetCaster();
            Unit* l_Target = GetHitUnit();
            
            if (l_Target == nullptr || l_Caster == nullptr)
                return;

            l_Caster->CastSpell(l_Target, l_Caster->HasAura(SPELL_WARR_WARBRINGER) ? SPELL_WARR_WARBRINGER_STUN : SPELL_WARR_CHARGE_ROOT, true);
        }

        void HandleRageGain(SpellEffIndex /*effIndex*/)
        {
            Unit* l_Caster = GetCaster();

            if (l_Caster != nullptr && !m_HasAuraDoubleTimeMarker)
            {
                int32 l_RageGain = GetEffectValue() / l_Caster->GetPowerCoeff(POWER_RAGE);

                l_Caster->EnergizeBySpell(l_Caster, GetSpellInfo()->Id, l_RageGain * l_Caster->GetPowerCoeff(POWER_RAGE), POWER_RAGE);
            }
        }

        void Register()
        {
            OnCast += SpellCastFn(spell_warr_charge_SpellScript::HandleOnCast);
            OnEffectHitTarget += SpellEffectFn(spell_warr_charge_SpellScript::HandleCharge, EFFECT_0, SPELL_EFFECT_CHARGE);
            OnEffectHitTarget += SpellEffectFn(spell_warr_charge_SpellScript::HandleRageGain, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_charge_SpellScript;
    }
};

/// Shield Wall - 871
class spell_warr_shield_wall: public SpellScriptLoader
{
    public:
        spell_warr_shield_wall() : SpellScriptLoader("spell_warr_shield_wall") { }

        class spell_warr_shield_wall_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_shield_wall_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->GetShield())
                        _player->AddAura(WARRIOR_SPELL_SHIELD_OF_WALL_NOSHIELD, _player);
                    else
                    {
                        if (_player->GetTeam() == HORDE)
                            _player->AddAura(WARRIOR_SPELL_SHIELD_OF_WALL_HORDE, _player);
                        else
                            _player->AddAura(WARRIOR_SPELL_SHIELD_OF_WALL_ALLIANCE, _player);
                    }
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(WARRIOR_SPELL_SHIELD_OF_WALL_NOSHIELD))
                        _player->RemoveAura(WARRIOR_SPELL_SHIELD_OF_WALL_NOSHIELD);
                    else if (_player->HasAura(WARRIOR_SPELL_SHIELD_OF_WALL_HORDE))
                        _player->RemoveAura(WARRIOR_SPELL_SHIELD_OF_WALL_HORDE);
                    else
                        _player->RemoveAura(WARRIOR_SPELL_SHIELD_OF_WALL_ALLIANCE);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warr_shield_wall_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_shield_wall_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_shield_wall_AuraScript();
        }
};

/// Spell Reflection - 23920
class spell_warr_spell_reflection: public SpellScriptLoader
{
    public:
        spell_warr_spell_reflection() : SpellScriptLoader("spell_warr_spell_reflection") { }

        class spell_warr_spell_reflection_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_spell_reflection_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->GetShield())
                        _player->AddAura(WARRIOR_SPELL_SPELL_REFLECTION_NOSHIELD, _player);
                    else
                    {
                        if (_player->GetTeam() == HORDE)
                            _player->AddAura(WARRIOR_SPELL_SPELL_REFLECTION_HORDE, _player);
                        else
                            _player->AddAura(WARRIOR_SPELL_SPELL_REFLECTION_ALLIANCE, _player);
                    }
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(WARRIOR_SPELL_SPELL_REFLECTION_NOSHIELD))
                        _player->RemoveAura(WARRIOR_SPELL_SPELL_REFLECTION_NOSHIELD);
                    else if (_player->HasAura(WARRIOR_SPELL_SPELL_REFLECTION_HORDE))
                        _player->RemoveAura(WARRIOR_SPELL_SPELL_REFLECTION_HORDE);
                    else
                        _player->RemoveAura(WARRIOR_SPELL_SPELL_REFLECTION_ALLIANCE);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warr_spell_reflection_AuraScript::OnApply, EFFECT_0, SPELL_AURA_REFLECT_SPELLS, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_spell_reflection_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_REFLECT_SPELLS, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_spell_reflection_AuraScript();
        }
};

/// last update : 6.1.2 19802
/// Intervene - 3411
class spell_warr_intervene: public SpellScriptLoader
{
    public:
        spell_warr_intervene() : SpellScriptLoader("spell_warr_intervene") { }

        class spell_warr_intervene_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_intervene_SpellScript);

            enum eSpells
            {
                InterveneAura = 34784,
                InterveneCharge = 147833
            };

            SpellCastResult CheckCast()
            {
                Player* l_Player = GetCaster()->ToPlayer();
                Unit* l_Target = GetExplTargetUnit();

                if (!l_Player || !l_Target)
                    return SPELL_FAILED_DONT_REPORT;

                if (l_Player->GetDistance(l_Target) >= 25.0f)
                    return SPELL_FAILED_OUT_OF_RANGE;

                return SPELL_CAST_OK;
            }

            void HandleOnCast()
            {
                Unit* l_Caster = GetCaster();
                Unit* l_Target = GetExplTargetUnit();

                if (l_Target == nullptr)
                    return;
                
                l_Caster->CastSpell(l_Target, eSpells::InterveneAura, true);
                l_Caster->CastSpell(l_Target, eSpells::InterveneCharge, true);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warr_intervene_SpellScript::CheckCast);
                OnCast += SpellCastFn(spell_warr_intervene_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_intervene_SpellScript();
        }
};

/// Called by Pummel - 6552 or Heroic Throw - 57755
class spell_warr_glyph_of_gag_order: public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_gag_order() : SpellScriptLoader("spell_warr_glyph_of_gag_order") { }

        class spell_warr_glyph_of_gag_order_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_glyph_of_gag_order_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (target->GetTypeId() != TYPEID_PLAYER)
                            caster->CastSpell(target, WARRIOR_SPELL_GAG_ORDER_SILENCE, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_glyph_of_gag_order_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_glyph_of_gag_order_SpellScript();
        }
};

/// Shield Barrier 174926 - Shield Barrier 112048
class spell_warr_shield_barrier: public SpellScriptLoader
{
    public:
        spell_warr_shield_barrier() : SpellScriptLoader("spell_warr_shield_barrier") { }

        class spell_warr_shield_barrier_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_shield_barrier_AuraScript);

            void CalculateAmount(constAuraEffectPtr /*aurEff*/, int32& p_Amount, bool& /*canBeRecalculated*/)
            {
                if (Unit* l_Caster = GetCaster())
                {
                    int8 l_RagetoUse = l_Caster->GetPower(POWER_RAGE) / l_Caster->GetPowerCoeff(POWER_RAGE);

                    if (l_RagetoUse > 40)
                        l_RagetoUse = 40;

                    p_Amount = l_Caster->GetTotalAttackPowerValue(WeaponAttackType::BaseAttack) * 1.4;
                    p_Amount += (p_Amount / 20) * l_RagetoUse;

                    l_Caster->ModifyPower(POWER_RAGE, -l_RagetoUse * l_Caster->GetPowerCoeff(POWER_RAGE));
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_shield_barrier_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_shield_barrier_AuraScript();
        }
};

enum AngerManagementSpells
{
    SPELL_WARR_ANGER_MANAGEMENT = 152278,
};

#define REDUCED_SPELLS_ID_MAX 13
uint32 g_ReducedSpellsId[REDUCED_SPELLS_ID_MAX] =
{
    107574, ///< Avatar
    12292,  ///< Bloodbath
    46924,  ///< Bladestorm
    107570, ///< Storm Bolt
    46968,  ///< Shockwave
    118000, ///< Dragon Roar
    114192, ///< Mocking Banner
    6544,   ///< Heroic Leap
    871,    ///< Shield Wall
    1160,   ///< Demoralizing Shout
    12975,  ///< Last Stand
    1719,   ///< Recklessness
    118038  ///< Die by the Sword
};

class spell_warr_anger_management: public PlayerScript
{
    public:
        spell_warr_anger_management() : PlayerScript("spell_warr_anger_management") {}

        uint16 m_RageSpend = 0;

        void OnModifyPower(Player* p_Player, Powers p_Power, int32 p_OldValue, int32& p_NewValue, bool p_Regen)
        {
            if (!p_Player || p_Player->getClass() != CLASS_WARRIOR || p_Power != POWER_RAGE || p_Regen || !p_Player->HasAura(SPELL_WARR_ANGER_MANAGEMENT))
                return;

            // Get the power earn (if > 0 ) or consum (if < 0)
            int32 l_diffValue = p_NewValue - p_OldValue;

            // Only get spended rage
            if (l_diffValue > 0)
                return;

            m_RageSpend += -l_diffValue / p_Player->GetPowerCoeff(POWER_RAGE);
            if (m_RageSpend >= sSpellMgr->GetSpellInfo(SPELL_WARR_ANGER_MANAGEMENT)->Effects[EFFECT_0].BasePoints)
            {
                for (int l_I = 0; l_I < REDUCED_SPELLS_ID_MAX; l_I++)
                {
                    if (p_Player->HasSpellCooldown(g_ReducedSpellsId[l_I]))
                        p_Player->ReduceSpellCooldown(g_ReducedSpellsId[l_I], 1 * IN_MILLISECONDS);
                }

                m_RageSpend = 0;
            }
        }
};

enum GlyphOfExecutor
{
    SpellWarrGlyphOfExecutor = 146971,
    SpellWarrGlyphOfExecutorEffect = 147352
};

/// Call by Execute - 5308 (Fury, Protection), Execute - 163201 (Arms)
/// Glyph of the Executor - 146971
class spell_warr_glyph_of_executor : public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_executor() : SpellScriptLoader("spell_warr_glyph_of_executor") { }

        class spell_warr_glyph_of_executor_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_glyph_of_executor_SpellScript);

            void HandleAfterHit()
            {
                Unit* l_Caster = GetCaster();
                Unit* l_Target = GetHitUnit();

                if (!l_Caster->ToPlayer())
                    return;

                SpellInfo const* l_SpellInfo = sSpellMgr->GetSpellInfo(GlyphOfExecutor::SpellWarrGlyphOfExecutor);

                if (l_Target == nullptr || l_SpellInfo == nullptr)
                    return;

                if (!l_Caster->HasAura(GlyphOfExecutor::SpellWarrGlyphOfExecutor))
                    return;

                if (!l_Target->isAlive()) ///< Killing an enemy with Execute grants you 30 rage.
                    l_Caster->CastSpell(l_Caster, GlyphOfExecutor::SpellWarrGlyphOfExecutorEffect, true);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warr_glyph_of_executor_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_glyph_of_executor_SpellScript();
        }
};

/// Execute (Arms) - 163201
/// last update : 6.1.2 19802
class spell_warr_execute: public SpellScriptLoader
{
    public:
        spell_warr_execute() : SpellScriptLoader("spell_warr_execute") { }

        class spell_warr_execute_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_execute_SpellScript);

            void HandleEnergize(SpellEffIndex p_EffIndex)
            {
                PreventHitDefaultEffect(p_EffIndex);
            }

            void HandleOnHit()
            {
                Unit* l_Caster = GetCaster();
                int32 l_Damage = GetHitDamage();

                /// If damage is 0 we should return script, to prevent double rage consuming
                if (l_Damage == 0)
                    return;

                int32 l_MaxConsumed = (GetSpellInfo()->Effects[EFFECT_2].BasePoints < 0 ? -GetSpellInfo()->Effects[EFFECT_2].BasePoints : GetSpellInfo()->Effects[EFFECT_2].BasePoints) * l_Caster->GetPowerCoeff(POWER_RAGE);

                /// consuming up to 30 additional Rage to deal up to 405% additional damage
                int32 l_RageConsumed = 0;
                
                if (l_Caster->GetPower(POWER_RAGE) > l_MaxConsumed)
                    l_RageConsumed = l_MaxConsumed;
                else
                    l_RageConsumed = l_Caster->GetPower(POWER_RAGE);

                /// Sudden Death : consume no extra Rage
                if (AuraPtr l_Aura = l_Caster->GetAura(52437))
                    l_Aura->Remove();
                else
                {
                    l_Caster->ModifyPower(POWER_RAGE, -l_RageConsumed);

                    // Should be % damage not % of the full amount, EFFECT_1 BP = 135% therefore 405 / 135 = 3 + 1 times more damage 
                    l_Damage *= (((l_RageConsumed * (405.0f / l_MaxConsumed)) / GetSpellInfo()->Effects[EFFECT_1].BasePoints) + 1);
                }

                if (l_Caster->HasAura(SPELL_WARRIOR_WEAPONS_MASTER))
                {
                    float l_MasteryValue = l_Caster->GetFloatValue(PLAYER_FIELD_MASTERY) * 3.5f;

                    l_Damage += CalculatePct(l_Damage, l_MasteryValue);
                }
                
                SetHitDamage(l_Damage);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_execute_SpellScript::HandleEnergize, EFFECT_2, SPELL_EFFECT_ENERGIZE);
                OnHit += SpellHitFn(spell_warr_execute_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_execute_SpellScript();
        }
};

enum WhirlwindSpells
{
    SpellWarrWirlwindOffHand    = 44949,
    SpellWarrWirlwindSpeArms    = 168695
};

/// Whirlwind - 1680
class spell_warr_whirlwind: public SpellScriptLoader
{
    public:
        spell_warr_whirlwind() : SpellScriptLoader("spell_warr_whirlwind") { }

        class spell_warr_whirlwind_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_whirlwind_SpellScript);

            void HandleOnCast()
            {
                Unit* l_Caster = GetCaster();

                if (l_Caster->HasAura(WARRIOR_ENHANCED_WHIRLWIND))
                {
                    l_Caster->CastSpell(l_Caster, WARROR_MEAT_CLEAVER_TARGET_MODIFIER, true);
                    if (AuraPtr l_MeatCleaverAura = l_Caster->GetAura(WARROR_MEAT_CLEAVER_TARGET_MODIFIER))
                    {
                        uint8 l_StackAmount = (l_MeatCleaverAura->GetStackAmount() + 1) > 4 ? 4 : l_MeatCleaverAura->GetStackAmount() + 1;
                        l_MeatCleaverAura->SetStackAmount(l_StackAmount);
                        l_MeatCleaverAura->RefreshDuration();
                        l_MeatCleaverAura->RefreshSpellMods();
                    }
                }
            }

            void HandleOnHit()
            {
                Player* l_Player = GetCaster()->ToPlayer();
                Unit* l_Target = GetHitUnit();
                if (!l_Player || !l_Target)
                    return;

                if (l_Player->GetSpecializationId(l_Player->GetActiveSpec()) == SPEC_WARRIOR_FURY)
                    l_Player->CastSpell(l_Target, WhirlwindSpells::SpellWarrWirlwindOffHand, true);
            }

            void HandleNormalizedWeaponDamage(SpellEffIndex p_EffIndex)
            {
                Player* l_Player = GetCaster()->ToPlayer();

                if (l_Player == nullptr)
                    return;

                if (l_Player->GetSpecializationId(l_Player->GetActiveSpec()) == SPEC_WARRIOR_ARMS)
                    PreventHitDefaultEffect(p_EffIndex);
            }

            void HandleWeaponPercentDamage(SpellEffIndex p_EffIndex)
            {
                Player* l_Player = GetCaster()->ToPlayer();

                if (l_Player == nullptr)
                    return;

                if (l_Player->GetSpecializationId(l_Player->GetActiveSpec()) == SPEC_WARRIOR_ARMS)
                {
                    PreventHitDefaultEffect(p_EffIndex);
                    l_Player->CastSpell(l_Player, WhirlwindSpells::SpellWarrWirlwindSpeArms, true);
                }
            }

            void Register()
            {
                OnEffectLaunch += SpellEffectFn(spell_warr_whirlwind_SpellScript::HandleNormalizedWeaponDamage, EFFECT_0, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
                OnEffectLaunch += SpellEffectFn(spell_warr_whirlwind_SpellScript::HandleWeaponPercentDamage, EFFECT_1, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
                OnHit += SpellHitFn(spell_warr_whirlwind_SpellScript::HandleOnHit);
                OnCast += SpellCastFn(spell_warr_whirlwind_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_whirlwind_SpellScript();
        }
};

enum ShieldChargeSpells
{
    SPELL_WARR_SHIELD_CHARGE_MODIFIER = 169667,
    SPELL_WARR_SHIELD_CHARGE_CHARGE = 178768
};

/// Shield Charge - 156321
class spell_warr_shield_charge: public SpellScriptLoader
{
    public:
        spell_warr_shield_charge() : SpellScriptLoader("spell_warr_shield_charge") { }

        class spell_warr_shield_charge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_shield_charge_SpellScript);

            void HandleOnCast()
            {
                Unit* l_Caster = GetCaster();
                Unit* l_Target = GetExplTargetUnit();
                if (!l_Target)
                    return;

                l_Caster->CastSpell(l_Target, SPELL_WARR_SHIELD_CHARGE_CHARGE, true);
                l_Caster->CastSpell(l_Caster, SPELL_WARR_SHIELD_CHARGE_MODIFIER, true);
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_warr_shield_charge_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_shield_charge_SpellScript();
        }
};

/// Execute - 5308 (Prot, Fury, Default)
/// last update : 6.1.2 19802
class spell_warr_execute_default: public SpellScriptLoader
{
    public:
        spell_warr_execute_default() : SpellScriptLoader("spell_warr_execute_default") { }

        class spell_warr_execute_default_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_execute_default_SpellScript);

            enum ExecuteSpells
            {
                SpellWarrExecuteOffHand = 163558
            };

            void HandleOnCast()
            {
                Player* l_Caster = GetCaster()->ToPlayer();
                Unit* l_Target = GetExplTargetUnit();
                if (!l_Caster || !l_Target)
                    return;

                if (l_Caster->GetSpecializationId(l_Caster->GetActiveSpec()) == SPEC_WARRIOR_FURY)
                    l_Caster->CastSpell(l_Target, ExecuteSpells::SpellWarrExecuteOffHand, true);
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_warr_execute_default_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_execute_default_SpellScript();
        }
};

/// Enhanced Rend - 174737
class spell_warr_enhanced_rend: public SpellScriptLoader
{
    public:
        spell_warr_enhanced_rend() : SpellScriptLoader("spell_warr_enhanced_rend") { }

        class spell_warr_enhanced_rend_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_enhanced_rend_AuraScript);

            enum eSpells
            {
                EnhancedRendDamage = 174736,
                Rend = 772
            };

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& l_ProcInfo)
            {
                PreventDefaultAction();

                if (Unit* l_Target = l_ProcInfo.GetActionTarget())
                {
                    if (Unit* l_Caster = GetCaster())
                    {
                        if (l_Target->HasAura(eSpells::Rend, l_Caster->GetGUID()))
                            l_Caster->CastSpell(l_Target, eSpells::EnhancedRendDamage, true);
                    }
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warr_enhanced_rend_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_enhanced_rend_AuraScript();
        }
};

/// Rend - 772
/// last update 6.1.2 19865
class spell_warr_rend : public SpellScriptLoader
{
    public:
        spell_warr_rend() : SpellScriptLoader("spell_warr_rend") { }

        class spell_warr_rend_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_rend_AuraScript);

            enum eSpells
            {
                RendFinalBurst = 94009
            };

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* l_Owner = GetCaster();
                Unit* l_Target = GetTarget();

                if (l_Owner == nullptr || l_Target == nullptr)
                    return;

                AuraRemoveMode l_RemoveMode = GetTargetApplication()->GetRemoveMode();

                if (l_RemoveMode != AURA_REMOVE_BY_EXPIRE)
                    return;

                l_Owner->CastSpell(l_Target, eSpells::RendFinalBurst, true);
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_rend_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_rend_AuraScript();
        }
};

/// BloodBath - 12292
class spell_warr_blood_bath : public SpellScriptLoader
{
    public:
        spell_warr_blood_bath() : SpellScriptLoader("spell_warr_blood_bath") { }

        class spell_warr_blood_bath_Aurascript : public AuraScript
        {
            PrepareAuraScript(spell_warr_blood_bath_Aurascript);

            enum eSpells
            {
                BloodBath       = 12292,
                BloodBathSnare  = 147531,
                BloodBathDamage = 113344
            };

            void HandleOnProc(constAuraEffectPtr /*aurEff*/, ProcEventInfo& p_ProcInfo)
            {
                PreventDefaultAction();

                if (!p_ProcInfo.GetDamageInfo() || !p_ProcInfo.GetDamageInfo()->GetDamage() || !p_ProcInfo.GetDamageInfo()->GetSpellInfo())
                    return;

                if (p_ProcInfo.GetDamageInfo()->GetSpellInfo()->Id == eSpells::BloodBathDamage)
                    return;

                Unit* l_Target = p_ProcInfo.GetActionTarget();
                Unit* l_Caster = GetCaster();
                if (l_Target == nullptr || l_Caster == nullptr || l_Target == l_Caster)
                    return;

                SpellInfo const* l_SpellInfo = sSpellMgr->GetSpellInfo(eSpells::BloodBath);
                SpellInfo const* l_SpellInfoDamage = sSpellMgr->GetSpellInfo(eSpells::BloodBathDamage);
                if (l_SpellInfo == nullptr || l_SpellInfoDamage == nullptr)
                    return;

                int32 l_Damage = CalculatePct(p_ProcInfo.GetDamageInfo()->GetDamage(), l_SpellInfo->Effects[EFFECT_0].BasePoints);

                int32 l_PreviousTotalDamage = 0;

                if (AuraEffectPtr l_PreviousBloodBath = l_Target->GetAuraEffect(eSpells::BloodBathDamage, EFFECT_0, l_Caster->GetGUID()))
                {
                    int32 l_PeriodicDamage = l_PreviousBloodBath->GetAmount();
                    int32 l_Duration = l_Target->GetAura(eSpells::BloodBathDamage, l_Caster->GetGUID())->GetDuration();
                    int32 l_Amplitude = l_PreviousBloodBath->GetAmplitude();

                    if (l_Amplitude)
                        l_PreviousTotalDamage = l_PeriodicDamage * (l_Duration / l_Amplitude);

                    l_PreviousTotalDamage /= (l_SpellInfoDamage->GetMaxDuration() / l_SpellInfoDamage->Effects[EFFECT_0].Amplitude);
                }

                if (l_SpellInfoDamage->Effects[EFFECT_0].Amplitude)
                    l_Damage /= (l_SpellInfoDamage->GetMaxDuration() / l_SpellInfoDamage->Effects[EFFECT_0].Amplitude);

                l_Damage += l_PreviousTotalDamage;

                l_Caster->CastSpell(l_Target, eSpells::BloodBathSnare, true);
                if (l_Target->HasAura(eSpells::BloodBathDamage, l_Caster->GetGUID()))
                {
                    if (AuraPtr l_ActualBloodBath = l_Target->GetAura(eSpells::BloodBathDamage, l_Caster->GetGUID()))
                        l_ActualBloodBath->SetDuration(l_ActualBloodBath->GetMaxDuration());
                }
                else
                    l_Caster->CastSpell(l_Target, eSpells::BloodBathDamage);
                if (AuraEffectPtr l_NewBloodBath = l_Target->GetAuraEffect(eSpells::BloodBathDamage, EFFECT_0, l_Caster->GetGUID()))
                    l_NewBloodBath->SetAmount(l_Damage);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warr_blood_bath_Aurascript::HandleOnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_blood_bath_Aurascript();
        }
};

enum SweepingStrikes
{
    SpellWarrGlyphOfSweepingStrikes         = 58384,
    SpellWarrSweepingStrikesRageBonus       = 124333
};

/// Sweeping Strikes (proc) - 12723
class spell_warr_sweeping_strikes : public SpellScriptLoader
{
    public:
        spell_warr_sweeping_strikes() : SpellScriptLoader("spell_warr_sweeping_strikes") { }

        class spell_warr_sweeping_strikes_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_sweeping_strikes_SpellScript);

            void HandleOnHit()
            {
                Unit* l_Caster = GetCaster();

                if (l_Caster->HasAura(SweepingStrikes::SpellWarrGlyphOfSweepingStrikes))
                    l_Caster->CastSpell(l_Caster, SweepingStrikes::SpellWarrSweepingStrikesRageBonus, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_sweeping_strikes_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_sweeping_strikes_SpellScript();
        }
};

enum BloodCrazeSpells
{
    SPELL_WARR_BLOOD_CRAZE_HEAL = 159363
};

/// Blood Craze - 159362
class spell_warr_blood_craze : public SpellScriptLoader
{
    public:
        spell_warr_blood_craze() : SpellScriptLoader("spell_warr_blood_craze") { }

        class spell_warr_blood_craze_Aurascript : public AuraScript
        {
            PrepareAuraScript(spell_warr_blood_craze_Aurascript);

            void HandleOnProc(constAuraEffectPtr p_AurEff, ProcEventInfo& p_ProcInfos)
            {
                PreventDefaultAction();

                if (p_ProcInfos.GetDamageInfo()->GetSpellInfo() != nullptr)
                    return;

                if (!(p_ProcInfos.GetHitMask() & PROC_EX_INTERNAL_MULTISTRIKE))
                    return;

                SpellInfo const* l_SpellInfo = sSpellMgr->GetSpellInfo(SPELL_WARR_BLOOD_CRAZE_HEAL);
                if (l_SpellInfo == nullptr || !l_SpellInfo->GetDuration())
                    return;

                if (Unit* l_Caster = GetCaster())
                {
                    /// 3% of your health over 3 sec.
                    int32 l_Health = CalculatePct(l_Caster->GetMaxHealth(), p_AurEff->GetAmount()) / (l_SpellInfo->GetDuration() / IN_MILLISECONDS);

                    l_Caster->CastCustomSpell(l_Caster, SPELL_WARR_BLOOD_CRAZE_HEAL, &l_Health, nullptr, nullptr, true);
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warr_blood_craze_Aurascript::HandleOnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_blood_craze_Aurascript();
        }
};

/// Blood Craze (aura) - 159363
class spell_warr_blood_craze_aura : public SpellScriptLoader
{
    public:
        spell_warr_blood_craze_aura() : SpellScriptLoader("spell_warr_blood_craze_aura") { }

        class spell_warr_blood_craze_aura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_blood_craze_aura_AuraScript);

            void OnApply(constAuraEffectPtr p_AurEff, AuraEffectHandleModes /*p_Mode*/)
            {
                Unit* l_Caster = GetCaster();

                if (l_Caster == nullptr)
                    return;

                /// 3% of your health over 3 sec.
                l_Caster->AddToStackOnDuration(GetSpellInfo()->Id, GetSpellInfo()->GetMaxDuration(), p_AurEff->GetAmount());
            }

            void OnUpdate(uint32 /*p_Diff*/, AuraEffectPtr p_AurEff)
            {
                Unit* l_Caster = GetCaster();

                if (l_Caster == nullptr)
                    return;

                StackOnDuration* l_Stack = l_Caster->GetStackOnDuration(GetSpellInfo()->Id);

                if (l_Stack == nullptr)
                    return;

                p_AurEff->SetAmount(l_Stack->GetTotalAmount());
            }

            void OnRemove(constAuraEffectPtr /*p_AurEff*/, AuraEffectHandleModes /*p_Mode*/)
            {
                Unit* l_Caster = GetCaster();

                if (l_Caster == nullptr)
                    return;

                l_Caster->RemoveStackOnDuration(GetSpellInfo()->Id);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warr_blood_craze_aura_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AuraEffectHandleModes(AURA_EFFECT_HANDLE_REAL | AURA_EFFECT_HANDLE_REAPPLY));
                OnEffectUpdate += AuraEffectUpdateFn(spell_warr_blood_craze_aura_AuraScript::OnUpdate, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_blood_craze_aura_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_blood_craze_aura_AuraScript();
        }
};

/// Meat Cleaver - 12950
/// last update 6.1.2 19865
class spell_warr_meat_cleaver : public SpellScriptLoader
{
    public:
        spell_warr_meat_cleaver() : SpellScriptLoader("spell_warr_meat_cleaver") { }

        class spell_warr_meat_cleaver_Aurascript : public AuraScript
        {
            PrepareAuraScript(spell_warr_meat_cleaver_Aurascript);

            enum eSpells
            {
                Whirlwind = 1680
            };

            void HandleOnProc(constAuraEffectPtr p_AurEff, ProcEventInfo& p_ProcInfo)
            {
                PreventDefaultAction();

                if (!p_ProcInfo.GetDamageInfo() || !p_ProcInfo.GetDamageInfo()->GetDamage())
                    return;

                if (!p_ProcInfo.GetDamageInfo()->GetSpellInfo() || p_ProcInfo.GetDamageInfo()->GetSpellInfo()->Id != eSpells::Whirlwind)
                    return;

                Unit* l_Caster = GetCaster();
                if (!l_Caster)
                    return;

                /// It procs on cast with Enhanced Whirlwind
                if (l_Caster->HasAura(WARRIOR_ENHANCED_WHIRLWIND))
                    return;

                l_Caster->CastSpell(l_Caster, WARROR_MEAT_CLEAVER_TARGET_MODIFIER, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warr_meat_cleaver_Aurascript::HandleOnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_meat_cleaver_Aurascript();
        }
};

/// last update : 6.1.2 19802
/// Shield Slam - 23922
class spell_warr_shield_slam : public SpellScriptLoader
{
    public:
        spell_warr_shield_slam() : SpellScriptLoader("spell_warr_shield_slam") { }

        class spell_warr_shield_slam_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_shield_slam_SpellScript);

            static float gte(int32 p_Level, int32 p_MinLevel)
            {
                if (p_Level < p_MinLevel)
                    return (float)p_MinLevel / 100;

                return (float)p_Level / 100;
            }

            void HandleDamage(SpellEffIndex /*p_EffIndex*/)
            {
                Unit* l_Caster = GetCaster();
                Unit* l_Target = GetHitUnit();

                if (l_Target == nullptr)
                    return;

                /// Formula : $apmult=${0.366+$gte($PL,80)*0.426+$gte($PL,85)*2.46}
                float l_ApMul = 0.366f + gte(l_Caster->getLevel(), 80) * 0.426f + gte(l_Caster->getLevel(), 85) * 2.46f;
                /// $gladmult=$?a156291[${1.05}][${1.0}] -> Already apply by Gladiator Stance
                /// $shieldchargemult=$?a169667[${1.25}][${1.0}] -> Already apply on spell_warr_shield_charge

                int32 l_Damage = l_Caster->GetTotalAttackPowerValue(WeaponAttackType::BaseAttack) * l_ApMul;

                l_Damage = l_Caster->SpellDamageBonusDone(l_Target, GetSpellInfo(), l_Damage, 0, SPELL_DIRECT_DAMAGE);
                l_Damage = l_Target->SpellDamageBonusTaken(l_Caster, GetSpellInfo(), l_Damage, SPELL_DIRECT_DAMAGE);

                /// Heavy Repercussions
                if (l_Caster->HasAura(WARRIOR_SPELL_SHIELD_BLOCK_TRIGGERED) || l_Caster->HasAura(SPELL_WARR_SHIELD_CHARGE_MODIFIER))
                    if (AuraPtr l_HeavyRepercussions = l_Caster->GetAura(WARRIOR_HEAVY_REPERCUSSIONS))
                        l_Damage += CalculatePct(l_Damage, l_HeavyRepercussions->GetEffect(0)->GetAmount());

                SetHitDamage(l_Damage);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_shield_slam_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_shield_slam_SpellScript();
        }
};

/// last update : 6.1.2 19802
/// Shattering Throw - 64382
class spell_warr_shattering_throw : public SpellScriptLoader
{
    public:
        spell_warr_shattering_throw() : SpellScriptLoader("spell_warr_shattering_throw") { }

        class spell_warr_shattering_throw_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_shattering_throw_SpellScript);

            enum eSpells
            {
                ShatteringThrowDispel = 64380,
            };

            void HandleDamage(SpellEffIndex /*p_EffIndex*/)
            {
                Player* l_Player = GetCaster()->ToPlayer();
                Unit* l_Target = GetHitUnit();

                if (l_Player == nullptr || l_Target == nullptr)
                    return;

                if (l_Target->IsImmunedToDamage(GetSpellInfo()))
                {
                    l_Player->CastSpell(l_Target, eSpells::ShatteringThrowDispel, true);
                    return;
                }

                if (l_Player->GetSpecializationId(l_Player->GetActiveSpec()) == SPEC_WARRIOR_FURY)
                    SetHitDamage(GetHitDamage() * 1.2f);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_shattering_throw_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_shattering_throw_SpellScript();
        }
};

/// last update : 6.1.2 19802
/// Glyph of Shattering Throw - 159759
class spell_warr_glyph_of_shattering_throw : public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_shattering_throw() : SpellScriptLoader("spell_warr_glyph_of_shattering_throw") { }

        class spell_warr_glyph_of_shattering_throw_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_glyph_of_shattering_throw_AuraScript);

            enum eSpells
            {
                ShatteringThrow = 64382
            };

            void OnApply(constAuraEffectPtr /*p_AurEff*/, AuraEffectHandleModes /*p_Mode*/)
            {
                Player* l_Player = GetTarget()->ToPlayer();

                if (l_Player == nullptr)
                    return;

                if (!l_Player->HasSpell(eSpells::ShatteringThrow))
                    l_Player->learnSpell(eSpells::ShatteringThrow, false);
            }

            void OnRemove(constAuraEffectPtr /*p_AurEff*/, AuraEffectHandleModes /*p_Mode*/)
            {
                Player* l_Player = GetTarget()->ToPlayer();

                if (l_Player == nullptr)
                    return;

                if (l_Player->HasSpell(eSpells::ShatteringThrow))
                    l_Player->removeSpell(eSpells::ShatteringThrow, false);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warr_glyph_of_shattering_throw_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_glyph_of_shattering_throw_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_glyph_of_shattering_throw_AuraScript();
        }
};

/// last update : 6.1.2 19802
/// Defensive Stance - 71
class spell_warr_defensive_stance : public SpellScriptLoader
{
    public:
        spell_warr_defensive_stance() : SpellScriptLoader("spell_warr_defensive_stance") { }

        enum eSpells
        {
            UnwaveringSentinel = 29144
        };

        class spell_warr_defensive_stance_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_defensive_stance_AuraScript);

            void OnApply(constAuraEffectPtr /*p_AurEff*/, AuraEffectHandleModes /*p_Mode*/)
            {
                Unit* l_Target = GetTarget();

                if (l_Target->HasSpell(eSpells::UnwaveringSentinel) && !l_Target->HasAura(eSpells::UnwaveringSentinel))
                    l_Target->CastSpell(l_Target, eSpells::UnwaveringSentinel, true);
            }

            void OnRemove(constAuraEffectPtr /*p_AurEff*/, AuraEffectHandleModes /*p_Mode*/)
            {
                Unit* l_Target = GetTarget();

                if (l_Target->HasAura(eSpells::UnwaveringSentinel))
                    l_Target->RemoveAura(eSpells::UnwaveringSentinel);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warr_defensive_stance_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_defensive_stance_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_defensive_stance_AuraScript();
        }
};

/// Single-Minded Fury - 81099
class spell_warr_single_minded_fury : public SpellScriptLoader
{
public:
    spell_warr_single_minded_fury() : SpellScriptLoader("spell_warr_single_minded_fury") { }

    class spell_warr_single_minded_fury_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_single_minded_fury_AuraScript);

        void CalculateFirstEffect(constAuraEffectPtr p_AurEff, int32& p_Amount, bool& p_CanBeRecalculated)
        {
            if (GetCaster() == nullptr)
                return;

            if (Player* l_Player = GetCaster()->ToPlayer())
            {
                Item* mainItem = l_Player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                Item* l_OffHandItem = l_Player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

                if (mainItem && l_OffHandItem)
                {
                    if (mainItem->GetTemplate()->IsTwoHandedWeapon() || l_OffHandItem->GetTemplate()->IsTwoHandedWeapon())
                        p_Amount = 0;
                }
                else
                    p_Amount = 0;
            }
        }

        void CalculateSecondEffect(constAuraEffectPtr p_AurEff, int32& p_Amount, bool& p_CanBeRecalculated)
        {
            if (GetCaster() == nullptr)
                return;

            if (Player* l_Player = GetCaster()->ToPlayer())
            {
                Item* mainItem = l_Player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                Item* l_OffHandItem = l_Player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

                if (mainItem && l_OffHandItem)
                {
                    if (mainItem->GetTemplate()->IsTwoHandedWeapon() || l_OffHandItem->GetTemplate()->IsTwoHandedWeapon())
                        p_Amount = 0;
                }
                else
                    p_Amount = 0;
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_single_minded_fury_AuraScript::CalculateFirstEffect, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_single_minded_fury_AuraScript::CalculateSecondEffect, EFFECT_1, SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warr_single_minded_fury_AuraScript();
    }
};

/// Called by Colossus Smash - 86346, Sweeping Strikes - 12328 and Recklessness - 1719
/// When theses abilities are casted while in Defensive Stance - 71, it should activate Battle Stance - 2457
class spell_warr_activate_battle_stance : public SpellScriptLoader
{
    public:
        spell_warr_activate_battle_stance() : SpellScriptLoader("spell_warr_activate_battle_stance") { }

        class spell_warr_activate_battle_stance_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_activate_battle_stance_SpellScript);

            enum eSpells
            {
                BattleStance = 2457
            };

            void HandleOnHit()
            {
                Unit* l_Caster = GetCaster();

                if (l_Caster->GetShapeshiftForm() == FORM_DEFENSIVESTANCE)
                    l_Caster->CastSpell(l_Caster, eSpells::BattleStance, true);
            }

            void Register()
            {
                BeforeHit += SpellHitFn(spell_warr_activate_battle_stance_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_activate_battle_stance_SpellScript();
        }
};

/// last update : 6.1.2 19802
/// Unyielding Strikes - 169685
class spell_warr_unyielding_strikes : public SpellScriptLoader
{
    public:
        spell_warr_unyielding_strikes() : SpellScriptLoader("spell_warr_unyielding_strikes") { }

        class spell_warr_unyielding_strikes_Aurascript : public AuraScript
        {
            PrepareAuraScript(spell_warr_unyielding_strikes_Aurascript);

            void HandleOnProc(constAuraEffectPtr /*p_AurEff*/, ProcEventInfo& /*p_ProcInfos*/)
            {
                PreventDefaultAction();
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warr_unyielding_strikes_Aurascript::HandleOnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_unyielding_strikes_Aurascript();
        }
};

/// last update : 6.1.2 19802
/// Heroic Strike - 78
class spell_warr_heroic_strike : public SpellScriptLoader
{
    public:
        spell_warr_heroic_strike() : SpellScriptLoader("spell_warr_heroic_strike") { }

        class spell_warr_heroic_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_heroic_strike_SpellScript);

            enum eSpells
            {
                UnyieldingStrikesProc = 169686
            };

            void HandleAfterHit()
            {
                Unit* l_Caster = GetCaster();

                if (l_Caster->HasAura(eSpells::UnyieldingStrikesProc))
                    l_Caster->RemoveAurasDueToSpell(eSpells::UnyieldingStrikesProc);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warr_heroic_strike_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_heroic_strike_SpellScript();
        }
};

/// last update : 6.1.2 19802
/// Call by Commanding Shout - 469, Battle Shout - 6673
/// Glyph of Mystic Shout - 58095, Glyph of Bloodcurdling Shout - 58096
class spell_warr_glyph_of_mystic_shout : public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_mystic_shout() : SpellScriptLoader("spell_warr_glyph_of_mystic_shout") { }

        class spell_warr_glyph_of_mystic_shout_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_glyph_of_mystic_shout_SpellScript);

            enum eSpells
            {
                GlyphofMystucShout = 58095,
                GlyphofMystucShoutAura = 121186,
                GlyphofBloodcurdlingShout = 58096,
                GlyphofBloodcurdlingShoutAura = 23690
            };

            void HandleOnCast()
            {
                Player* l_Player = GetCaster()->ToPlayer();

                if (l_Player == nullptr)
                    return;

                if (l_Player->HasGlyph(eSpells::GlyphofBloodcurdlingShout))
                    l_Player->CastSpell(l_Player, eSpells::GlyphofBloodcurdlingShoutAura, true);
                if (l_Player->HasGlyph(eSpells::GlyphofMystucShout))
                    l_Player->CastSpell(l_Player, eSpells::GlyphofMystucShoutAura, true);
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_warr_glyph_of_mystic_shout_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_glyph_of_mystic_shout_SpellScript();
        }
};

/// last update : 6.1.2 19802
/// Glyph of Crow Feast - 115943
class spell_warr_glyph_of_crow_feast : public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_crow_feast() : SpellScriptLoader("spell_warr_glyph_of_crow_feast") { }

        class spell_warr_glyph_of_crow_feast_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_glyph_of_crow_feast_AuraScript);

            enum eSpells
            {
                Execute = 5308,
                GlyphOfCrowFeast = 115944
            };

            void OnProc(constAuraEffectPtr /*p_AurEff*/, ProcEventInfo& p_ProcEventInfo)
            {
                PreventDefaultAction();

                if (p_ProcEventInfo.GetDamageInfo() == nullptr)
                    return;

                Unit* l_Caster = GetCaster();
                Unit* l_Target = p_ProcEventInfo.GetDamageInfo()->GetVictim();
                SpellInfo const* l_SpellInfoTriggerSpell = p_ProcEventInfo.GetDamageInfo()->GetSpellInfo();

                if (l_Caster == nullptr || l_Target == nullptr || l_SpellInfoTriggerSpell == nullptr)
                    return;

                if (l_SpellInfoTriggerSpell->Id != eSpells::Execute)
                    return;

                if (!(p_ProcEventInfo.GetHitMask() & PROC_EX_CRITICAL_HIT))
                    return;

                l_Caster->CastSpell(l_Target, eSpells::GlyphOfCrowFeast, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warr_glyph_of_crow_feast_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_glyph_of_crow_feast_AuraScript();
        }
};

void AddSC_warrior_spell_scripts()
{
    new spell_warr_glyph_of_crow_feast();
    new spell_warr_glyph_of_mystic_shout();
    new spell_warr_heroic_strike();
    new spell_warr_unyielding_strikes();
    new spell_warr_defensive_stance();
    new spell_warr_glyph_of_shattering_throw();
    new spell_warr_shattering_throw();
    new spell_warr_sweeping_strikes();
    new spell_warr_ravager();
    new spell_warr_rend();
    new spell_warr_victorious_state();
    new spell_warr_glyph_of_hindering_strikes();
    new spell_warr_shield_block();
    new spell_warr_storm_bolt();
    new spell_warr_colossus_smash();
    new spell_warr_dragon_roar();
    new spell_warr_staggering_shout();
    new spell_warr_second_wind();
    new spell_warr_berzerker_rage();
    new spell_warr_enrage();
    new spell_warr_mocking_banner();
    new spell_warr_raging_blow();
    new spell_warr_devaste();
    new spell_warr_mortal_strike();
    new spell_warr_rallying_cry();
    new spell_warr_heroic_leap_damage();
    new spell_warr_heroic_leap();
    new spell_warr_shockwave();
    new spell_warr_glyph_of_raging_blow();
    new spell_warr_bloodthirst();
    new spell_warr_bloodthirst_heal();
    new spell_warr_victory_rush();
    new spell_warr_victory_rush_heal();
    new spell_warr_deep_wounds();
    new spell_warr_charge();
    new spell_warr_shield_wall();
    new spell_warr_spell_reflection();
    new spell_warr_intervene();
    new spell_warr_glyph_of_gag_order();
    new spell_warr_shield_barrier();
    new spell_warr_anger_management();
    new spell_warr_execute();
    new spell_warr_whirlwind();
    new spell_warr_shield_charge();
    new spell_warr_execute_default();
    new spell_warr_enhanced_rend();
    new spell_warr_blood_bath();
    new spell_warr_blood_craze();
    new spell_warr_glyph_of_executor();
    new spell_warr_meat_cleaver();
    new spell_warr_shield_slam();
    new spell_warr_blood_craze_aura();
    new spell_warr_glyph_of_die_by_the_sword();
    new spell_warr_single_minded_fury();
    new spell_warr_activate_battle_stance();

    /// Playerscripts
    new PlayerScript_second_wind();
}