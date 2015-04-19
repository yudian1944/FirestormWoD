#80167/NPC - Groog

	UPDATE `creature_template` SET `minlevel` = 90,`maxlevel` = 90,`exp` = 5,`ScriptName` = 'npc_groog' WHERE `entry` = 80167;
	INSERT INTO spell_script_names VALUE (148852,"spell_groog_rampage");

	UPDATE `creature_template` SET `lootid`=80167 WHERE `entry`=80167;
	DELETE FROM `creature_loot_template` WHERE `entry`=80167;

	INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`,`itemBonuses`) VALUES
	(80167,106283,0.24,1,0,1,1,'') /* 8Ripped Mail Shoulderpads */,
	(80167,106284,0.49,1,0,1,1,'') /* 8Scraggly Cloth Shoulderpads */,
	(80167,106285,0.29,1,0,1,1,'') /* 8Acid Scarred Plate Belt */,
	(80167,106286,0.73,1,0,1,1,'') /* 8Sun-Baked Belt */,
	(80167,106287,0.63,1,0,1,1,'') /* 8Scraggly Cloth Belt */,
	(80167,106288,0.44,1,0,1,1,'') /* 8Ripped Mail Belt */,
	(80167,106289,0.15,1,0,1,1,'') /* 8Sun-Baked Bracers */,
	(80167,106290,0.58,1,0,1,1,'') /* 8Scraggly Cloth Bracers */,
	(80167,106291,0.44,1,0,1,1,'') /* 8Ripped Mail Bracers */,
	(80167,106292,0.24,1,0,1,1,'') /* 8Acid Scarred Plate Bracers */,
	(80167,106293,0.49,1,0,1,1,'') /* 8Sun-Baked Pants */,
	(80167,106294,0.49,1,0,1,1,'') /* 8Acid Scarred Plate Pants */,
	(80167,106295,0.58,1,0,1,1,'') /* 8Ripped Mail Pants */,
	(80167,106296,0.34,1,0,1,1,'') /* 8Scraggly Cloth Pants */,
	(80167,106297,0.44,1,0,1,1,'') /* 8Sun-Baked Shoulderpads */,
	(80167,106298,0.39,1,0,1,1,'') /* 8Acid Scarred Plate Shoulderpads */,
	(80167,106299,0.49,1,0,1,1,'') /* 8Ripped Mail Boots */,
	(80167,106300,0.39,1,0,1,1,'') /* 8Acid Scarred Plate Boots */,
	(80167,106301,0.63,1,0,1,1,'') /* 8Sun-Baked Gloves */,
	(80167,106302,0.68,1,0,1,1,'') /* 8Acid Scarred Plate Gloves */,
	(80167,106303,0.68,1,0,1,1,'') /* 8Ripped Mail Gloves */,
	(80167,106304,0.73,1,0,1,1,'') /* 8Scraggly Cloth Gloves */,
	(80167,106305,0.58,1,0,1,1,'') /* 8Acid Scarred Plate Helmet */,
	(80167,106306,0.15,1,0,1,1,'') /* 8Scraggly Hat */,
	(80167,106307,0.49,1,0,1,1,'') /* 8Sun-Baked Leather Helmet */,
	(80167,106308,0.24,1,0,1,1,'') /* 8Ripped Mail Circlet */,
	(80167,106309,0.68,1,0,1,1,'') /* 8Sun-Baked Armor */,
	(80167,106310,0.44,1,0,1,1,'') /* 8Acid Scarred Plate Chestpiece */,
	(80167,106312,0.49,1,0,1,1,'') /* 8Scraggly Cloth Vest */,
	(80167,106313,0.58,1,0,1,1,'') /* 8Sun-Baked Boots */,
	(80167,106314,0.29,1,0,1,1,'') /* 8Scraggly Cloth Boots */,
	(80167,106315,0.15,1,0,1,1,'') /* 8Jammed Pocketknife */,
	(80167,106316,0.58,1,0,1,1,'') /* 8Half-Handle Mace */,
	(80167,106317,0.29,1,0,1,1,'') /* 8Brittle Blade */,
	(80167,106318,0.68,1,0,1,1,'') /* 8Blunt Logging Axe */,
	(80167,106319,0.53,1,0,1,1,'') /* 8Knog's Bow of Surrender */,
	(80167,106320,0.44,1,0,1,1,'') /* 8Narrcho's Rifle of Unreadiness */,
	(80167,106321,0.63,1,0,1,1,'') /* 8Cracked-Haft Cleaver */,
	(80167,106322,0.39,1,0,1,1,'') /* 8Brittle Greatsword */,
	(80167,106323,0.53,1,0,1,1,'') /* 8Poorly Balanced Warhammer */,
	(80167,106324,0.49,1,0,1,1,'') /* 8Robble's Staff of Herding */,
	(80167,106391,0.15,1,0,1,1,'') /* 6Bladespire Gauntlets */,
	(80167,106393,0.05,1,0,1,1,'') /* 6Bladespire Helm */,
	(80167,106399,0.1,1,0,1,1,'') /* 6Coldsnout Bindings */,
	(80167,106403,0.19,1,0,1,1,'') /* 6Coldsnout Hood */,
	(80167,106411,0.05,1,0,1,1,'') /* 6Lunarglow Robe */,
	(80167,106416,0.05,1,0,1,1,'') /* 6Frostlink Bracers */,
	(80167,106422,0.24,1,0,1,1,'') /* 6Frostlink Vest */,
	(80167,106423,0.05,1,0,1,1,'') /* 6Rimeplate Breastplate */,
	(80167,106425,0.1,1,0,1,1,'') /* 6Rimeplate Girdle */,
	(80167,106426,0.05,1,0,1,1,'') /* 6Rimeplate Helm */,
	(80167,106429,0.05,1,0,1,1,'') /* 6Rimeplate Sabatons */,
	(80167,106434,0.24,1,0,1,1,'') /* 6Voidcaller Britches */,
	(80167,106443,0.05,1,0,1,1,'') /* 6Anchorite Leggings */,
	(80167,106452,0.05,1,0,1,1,'') /* 6Gronnling Helm */,
	(80167,106454,0.1,1,0,1,1,'') /* 6Gronnling Spaulders */,
	(80167,106455,0.05,1,0,1,1,'') /* 6Gronnling Vest */,
	(80167,111349,0.24,1,0,1,1,'') /* 5A Treatise on Mining in Draenor */,
	(80167,111364,36,1,0,1,1,'') /* 5First Aid in Draenor */,
	(80167,111387,36,1,0,1,1,'') /* 5The Joy of Draenor Cooking */,
	(80167,113295,2,1,0,1,1,'') /* 7Cracked Potion Vial */,
	(80167,113321,0.29,1,0,1,1,'') /* 7Battered Shield */,
	(80167,113327,0.29,1,0,1,1,'') /* 7Weathered Bedroll */,
	(80167,113328,0.39,1,0,1,1,'') /* 7Torn Voodoo Doll */,
	(80167,113429,0.29,1,0,1,1,'') /* 7Cracked Hand Drum */,
	(80167,113465,0.49,1,0,1,1,'') /* 7Broken Hunting Scope */,
	(80167,113478,3,1,0,1,1,'') /* 7Abandoned Medic Kit */,
	(80167,116173,-0.05,1,0,1,1,'') /* 5Tattered Frostwolf Shroud */,
	(80167,116461,0.05,1,0,1,1,'') /* 6Frostbitten Dagger */,
	(80167,116467,0.24,1,0,1,1,'') /* 6Frostbitten Hammer */,
	(80167,116470,0.05,1,0,1,1,'') /* 6Frostbitten Staff */,
	(80167,116475,0.1,1,0,1,1,'') /* 6Lunarglow Broadaxe */,
	(80167,116488,0.15,1,0,1,1,'') /* 6Lunarglow Sword */,
	(80167,116677,0.05,1,0,1,1,'') /* 6Coldsinger Amulet */,
	(80167,116693,0.29,1,0,1,1,'') /* 6Coldsinger Cloak */,
	(80167,116696,0.24,1,0,1,1,'') /* 6Moonwhisper Cloak */,
	(80167,118782,0.05,1,0,1,1,'') /* 5Ivory-Hilted Cleaver */,
	(80167,118835,0.05,1,0,1,1,'') /* 5Kiraser's Gloves of Precision */;