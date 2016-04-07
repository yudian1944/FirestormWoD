////////////////////////////////////////////////////////////////////////////////
//
//  MILLENIUM-STUDIO
//  Copyright 2016 Millenium-studio SARL
//  All Rights Reserved.
//
////////////////////////////////////////////////////////////////////////////////

/* Script Data Start
SDName: Boss mal_ganis
SDAuthor: Tartalo
SD%Complete: 80
SDComment: TODO: Intro & outro
SDCategory:
Script Data End */

#include "ScriptPCH.h"
#include "culling_of_stratholme.h"

enum Spells
{
    SPELL_CARRION_SWARM                         = 52720, //A cresting wave of chaotic magic splashes over enemies in front of the caster, dealing 3230 to 3570 Shadow damage and 380 to 420 Shadow damage every 3 sec. for 15 sec.
    H_SPELL_CARRION_SWARM                       = 58852,
    SPELL_MIND_BLAST                            = 52722, //Inflicts 4163 to 4837 Shadow damage to an enemy.
    H_SPELL_MIND_BLAST                          = 58850,
    SPELL_SLEEP                                 = 52721, //Puts an enemy to sleep for up to 10 sec. Any damage caused will awaken the target.
    H_SPELL_SLEEP                               = 58849,
    SPELL_VAMPIRIC_TOUCH                        = 52723, //Heals the caster for half the damage dealt by a melee attack.
    SPELL_KILL_CREDIT                           = 58630  // Non-existing spell as encounter credit, created in spell_dbc
};

enum Yells
{
    SAY_INTRO_1                                 = -1595009,
    SAY_INTRO_2                                 = -1595010,
    SAY_AGGRO                                   = -1595011,
    SAY_KILL_1                                  = -1595012,
    SAY_KILL_2                                  = -1595013,
    SAY_KILL_3                                  = -1595014,
    SAY_SLAY_1                                  = -1595015,
    SAY_SLAY_2                                  = -1595016,
    SAY_SLAY_3                                  = -1595017,
    SAY_SLAY_4                                  = -1595018,
    SAY_SLEEP_1                                 = -1595019,
    SAY_SLEEP_2                                 = -1595020,
    SAY_30HEALTH                                = -1595021,
    SAY_15HEALTH                                = -1595022,
    SAY_ESCAPE_SPEECH_1                         = -1595023,
    SAY_ESCAPE_SPEECH_2                         = -1595024,
    SAY_OUTRO                                   = -1595025
};

enum CombatPhases
{
    COMBAT,
    OUTRO
};

class boss_mal_ganis : public CreatureScript
{
public:
    boss_mal_ganis() : CreatureScript("boss_mal_ganis") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_mal_ganisAI (creature);
    }

    struct boss_mal_ganisAI : public ScriptedAI
    {
        boss_mal_ganisAI(Creature* c) : ScriptedAI(c)
        {
            instance = c->GetInstanceScript();
        }

        uint32 uiCarrionSwarmTimer;
        uint32 uiMindBlastTimer;
        uint32 uiVampiricTouchTimer;
        uint32 uiSleepTimer;

        uint8 uiOutroStep;
        uint32 uiOutroTimer;

        bool bYelled;
        bool bYelled2;

        CombatPhases Phase;

        InstanceScript* instance;

        void Reset()
        {
             bYelled = false;
             bYelled2 = false;
             Phase = COMBAT;
             uiCarrionSwarmTimer = 6000;
             uiMindBlastTimer = 11000;
             uiVampiricTouchTimer = urand(10000, 15000);
             uiSleepTimer = urand(15000, 20000);
             uiOutroTimer = 1000;

             if (instance)
                 instance->SetData(DATA_MAL_GANIS_EVENT, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);
            if (instance)
                instance->SetData(DATA_MAL_GANIS_EVENT, IN_PROGRESS);
        }

        void DamageTaken(Unit* done_by, uint32 &damage, SpellInfo const* p_SpellInfo)
        {
            if (damage >= me->GetHealth() && done_by != me)
                damage = me->GetHealth()-1;
        }

        void UpdateAI(const uint32 diff)
        {
            switch (Phase)
            {
                case COMBAT:
                    //Return since we have no target
                    if (!UpdateVictim())
                        return;

                    if (!bYelled && HealthBelowPct(30))
                    {
                        DoScriptText(SAY_30HEALTH, me);
                        bYelled = true;
                    }

                    if (!bYelled2 && HealthBelowPct(15))
                    {
                        DoScriptText(SAY_15HEALTH, me);
                        bYelled2 = true;
                    }

                    if (HealthBelowPct(1))
                    {
                        //Handle Escape Event: Don't forget to add Player::RewardPlayerAndGroupAtEvent
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        uiOutroStep = 1;
                        Phase = OUTRO;
                        return;
                    }

                    if (Creature* pArthas = me->GetCreature(*me, instance ? instance->GetData64(DATA_ARTHAS) : 0))
                        if (pArthas->isDead())
                        {
                            EnterEvadeMode();
                            me->DisappearAndDie();
                            if (instance)
                                instance->SetData(DATA_MAL_GANIS_EVENT, FAIL);
                        }

                    if (uiCarrionSwarmTimer < diff)
                    {
                        DoCastVictim(SPELL_CARRION_SWARM);
                        uiCarrionSwarmTimer = 7000;
                    } else uiCarrionSwarmTimer -= diff;

                    if (uiMindBlastTimer < diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(target, SPELL_MIND_BLAST);
                        uiMindBlastTimer = 6000;
                    } else uiMindBlastTimer -= diff;

                    if (uiVampiricTouchTimer < diff)
                    {
                        DoCast(me, SPELL_VAMPIRIC_TOUCH);
                        uiVampiricTouchTimer = 32000;
                    } else uiVampiricTouchTimer -= diff;

                    if (uiSleepTimer < diff)
                    {
                        DoScriptText(RAND(SAY_SLEEP_1, SAY_SLEEP_2), me);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(target, SPELL_SLEEP);
                        uiSleepTimer = urand(15000, 20000);
                    } else uiSleepTimer -= diff;

                    DoMeleeAttackIfReady();
                    break;
                case OUTRO:
                    if (uiOutroTimer < diff)
                    {
                        switch (uiOutroStep)
                        {
                            case 1:
                                DoScriptText(SAY_ESCAPE_SPEECH_1, me);
                                me->GetMotionMaster()->MoveTargetedHome();
                                ++uiOutroStep;
                                uiOutroTimer = 8000;
                                break;
                            case 2:
                                me->SetGuidValue(UNIT_FIELD_TARGET, instance ? instance->GetData64(DATA_ARTHAS) : 0);
                                me->HandleEmoteCommand(29);
                                DoScriptText(SAY_ESCAPE_SPEECH_2, me);
                                ++uiOutroStep;
                                uiOutroTimer = 9000;
                                break;
                            case 3:
                                DoScriptText(SAY_OUTRO, me);
                                ++uiOutroStep;
                                uiOutroTimer = 16000;
                                break;
                            case 4:
                                me->HandleEmoteCommand(33);
                                ++uiOutroStep;
                                uiOutroTimer = 500;
                                break;
                            case 5:
                                me->SetVisible(false);
                                me->Kill(me);
                                break;

                        }
                    } else uiOutroTimer -= diff;
                    break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            if (instance)
            {
                instance->SetData(DATA_MAL_GANIS_EVENT, DONE);

                // give achievement credit and LFG rewards to players. criteria use spell 58630 which doesn't exist, but it was created in spell_dbc
                DoCast(me, SPELL_KILL_CREDIT);
                instance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_KILL_CREDIT);

                if (GameObject* go = me->SummonGameObject(IsHeroic() ? GO_MALGANIS_CHEST_H : GO_MALGANIS_CHEST_N, 2288.35f, 1498.73f, 128.414f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, DAY))
                    go->RemoveFlag(GAMEOBJECT_FIELD_FLAGS, GO_FLAG_INTERACT_COND);
            }
        }

        void KilledUnit(Unit* victim)
        {
            if (victim == me)
                return;

            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2, SAY_SLAY_3, SAY_SLAY_4), me);
        }
    };

};

#ifndef __clang_analyzer__
void AddSC_boss_mal_ganis()
{
    new boss_mal_ganis();
}
#endif