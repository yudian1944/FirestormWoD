-- Ji-Kun / Trone of thunder

-- 69712 - Ji-Kun alternative templates
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
('469712','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46675','0','0','0','Ji-Kun (4)','','','0','93','93','4','0','14','14','0','0','1','1.14286','1.14286','1','3','15000','30000','0','0','6','1500','0','4','0','0','0','0','0','0','0','0','0','0','0','1','2097260','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','3000000','3100000','','0','4','1', '479','1','1','1','0','0','0','0','0','0','0','0','1','0','769638399','1','boss_ji_kun','17614'),
('569712','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46675','0','0','0','Ji-Kun (5)','','','0','93','93','4','0','14','14','0','0','1','1.14286','1.14286','1','3','15000','30000','0','0','7','1500','0','4','0','0','0','0','0','0','0','0','0','0','0','1','2097260','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','3000000','3100000','','0','4','1','1440','1','1','1','0','0','0','0','0','0','0','0','1','0','769638399','1','boss_ji_kun','17614'),
('669712','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46675','0','0','0','Ji-Kun (6)','','','0','93','93','4','0','14','14','0','0','1','1.14286','1.14286','1','3','15000','30000','0','0','9','1500','0','4','0','0','0','0','0','0','0','0','0','0','0','1','2097260','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','3000000','3100000','','0','4','1', '720','1','1','1','0','0','0','0','0','0','0','0','1','0','769638399','1','boss_ji_kun','17614'),
('769712','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46675','0','0','0','Ji-Kun (7)','','','0','93','93','4','0','14','14','0','0','1','1.14286','1.14286','1','3','15000','30000','0','0','7','1500','0','4','0','0','0','0','0','0','0','0','0','0','0','1','2097260','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','3000000','3100000','','0','4','1', '990','1','1','1','0','0','0','0','0','0','0','0','1','0','769638399','1','boss_ji_kun','17614');

-- Main template update
UPDATE `creature_template` SET
`mechanic_immune_mask` = 769638399,
difficulty_entry_4 = 469712,
difficulty_entry_5 = 569712,
difficulty_entry_6 = 669712,
difficulty_entry_7 = 769712,
flags_extra = 1,
Health_mod = 480
WHERE `entry` = 69712;

-- 68194 - Young Egg of Ji-Kun
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
('468194','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46683','0','0','0','Young Egg of Ji-Kun (4)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','6','2000','2000','1','256','2097152','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','2.4','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_young_egg_of_jikun','17614'),
('568194','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46683','0','0','0','Young Egg of Ji-Kun (5)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','7','2000','2000','1','256','2097152','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','3.6','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_young_egg_of_jikun','17614'),
('668194','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46683','0','0','0','Young Egg of Ji-Kun (6)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','9','2000','2000','1','256','2097152','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','4.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_young_egg_of_jikun','17614'),
('768194','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46683','0','0','0','Young Egg of Ji-Kun (7)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','7','2000','2000','1','256','2097152','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','2.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_young_egg_of_jikun','17614');

UPDATE creature_template SET
difficulty_entry_4 = 468194,
difficulty_entry_5 = 568194,
difficulty_entry_6 = 668194,
difficulty_entry_7 = 768194,
mindmg = 9838, maxdmg = 14331
WHERE entry = 68194;

-- 68192 - Hatchling
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
('468192','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46680','0','0','0','Hatchling (4)','','','0','92','92','4','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','42296','6','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','2.4','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_hatchling','17614'),
('568192','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46680','0','0','0','Hatchling (5)','','','0','92','92','4','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','42296','7','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','3.6','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_hatchling','17614'),
('668192','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46680','0','0','0','Hatchling (6)','','','0','92','92','4','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','42296','9','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','3.6','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_hatchling','17614'),
('768192','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','46680','0','0','0','Hatchling (7)','','','0','92','92','4','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','42296','7','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','2.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_hatchling','17614');

UPDATE creature_template SET
difficulty_entry_4 = 468192,
difficulty_entry_5 = 468192,
difficulty_entry_6 = 668192,
difficulty_entry_7 = 768192,
mindmg = 9838, maxdmg = 14331,
Health_mod = 2.4
WHERE entry = 68192;

-- 68202 - Ji-Kun Fledgling's Egg
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
('468202','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47701','0','0','0','Ji-Kun Fledgling\'s Egg (4)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','4','2000','2000','1','256','2048','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','4.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_fledgling_egg','17614'),
('568202','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47701','0','0','0','Ji-Kun Fledgling\'s Egg (5)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','7','2000','2000','1','256','2048','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','6.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_fledgling_egg','17614'),
('668202','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47701','0','0','0','Ji-Kun Fledgling\'s Egg (6)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','9','2000','2000','1','256','2048','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','6.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_fledgling_egg','17614'),
('768202','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47701','0','0','0','Ji-Kun Fledgling\'s Egg (7)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','7','2000','2000','1','256','2048','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','4',  '1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_fledgling_egg','17614');

UPDATE creature_template SET
difficulty_entry_4 = 468202,
difficulty_entry_5 = 568202,
difficulty_entry_6 = 668202,
difficulty_entry_7 = 768202,
mindmg = 9838, maxdmg = 14331,
Health_mod = 3.6
WHERE entry = 68202;

-- 69628 - Mature Egg of Ji-Kun
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
('469628','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47702','0','0','0','Mature Egg of Ji-Kun (4)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','4','2000','2000','1','256','2048','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','4.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_fledgling_egg','17614'),
('569628','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47702','0','0','0','Mature Egg of Ji-Kun (5)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','7','2000','2000','1','256','2048','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','5.2','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_fledgling_egg','17614'),
('669628','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47702','0','0','0','Mature Egg of Ji-Kun (6)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','9','2000','2000','1','256','2048','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','6.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_fledgling_egg','17614'),
('769628','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47702','0','0','0','Mature Egg of Ji-Kun (7)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','7','2000','2000','1','256','2048','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','4',  '1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_fledgling_egg','17614');

UPDATE creature_template SET
difficulty_entry_4 = 469628,
difficulty_entry_4 = 469628,
difficulty_entry_4 = 469628,
difficulty_entry_4 = 469628,
mindmg = 9838, maxdmg = 14331,
Health_mod = 3.6
WHERE entry = 69628;

-- 70095 - Juvenile
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
('470095','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47709','0','0','0','Juvenile (4)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','4','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','7','1','4.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_juvenile','17614'),
('570095','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47709','0','0','0','Juvenile (5)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','7','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','7','1','6.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_juvenile','17614'),
('670095','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47709','0','0','0','Juvenile (6)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','9','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','7','1','6.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_juvenile','17614'),
('770095','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47709','0','0','0','Juvenile (7)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','7','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','7','1','4',  '1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_juvenile','17614');

UPDATE creature_template SET
difficulty_entry_4 = 470095,
difficulty_entry_4 = 470095,
difficulty_entry_4 = 470095,
difficulty_entry_4 = 470095,
mindmg = 9838, maxdmg = 14331
WHERE entry = 70095;

-- 69836 - Juvenile
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
('469836','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47709','0','0','0','Juvenile (4)','','','0','92','92','4','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','4','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','7','1','4.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_juvenile','17614'),
('569836','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47709','0','0','0','Juvenile (5)','','','0','92','92','4','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','7','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','7','1','5.2','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_juvenile','17614'),
('669836','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47709','0','0','0','Juvenile (6)','','','0','92','92','4','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','9','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','7','1','6.5','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_juvenile','17614'),
('769836','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47709','0','0','0','Juvenile (7)','','','0','92','92','4','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','7','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','7','1','4',  '1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_juvenile','17614');

UPDATE creature_template SET
difficulty_entry_4 = 469836,
difficulty_entry_5 = 569836,
difficulty_entry_6 = 669836,
difficulty_entry_7 = 769836,
baseattacktime = 2000,
rangeattacktime = 2000
WHERE entry = 69836;

-- 70134 - Nest Guardian  - Heroic only
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
('670134','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','47883','0','0','0','Nest Guardian (6)','','','0','92','92','0','0','14','14','0','0','1','1.14286','1.14286','1','1','9838','14331','0','0','7','2000','2000','1','0','0','0','0','0','0','0','0','0','0','0','1','2097224','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','10','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','mob_nest_guardian','17614');

UPDATE creature_template SET
difficulty_entry_5 = 670134,
mindmg = 9838, maxdmg = 14331,
dmg_multiplier = 4,
Health_mod = 6.4
WHERE entry = 70134;