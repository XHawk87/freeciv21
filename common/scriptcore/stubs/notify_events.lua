---@meta

-- Copyright (c) 1996-2020 Freeciv21 and Freeciv contributors. This file is
-- part of Freeciv21. Freeciv21 is free software: you can redistribute it
-- and/or modify it under the terms of the GNU  General Public License  as
-- published by the Free Software Foundation, either version 3 of the
-- License,  or (at your option) any later version. You should have received
-- a copy of the GNU General Public License along with Freeciv21. If not,
-- see https://www.gnu.org/licenses/.

-- SPDX-License-Identifier: GPL-3.0-or-later
-- SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors
-- SPDX-FileCopyrightText: XHawk87 <hawk87@hotmail.co.uk>

--  WARNING: do not attempt to change the name of the API functions.
--  They may be in use in Lua scripts in savefiles, so once released, the
--  name and signature cannot change shape even in new major versions of
--  Freeciv, until the relevant save format version can no longer be loaded.
--  If you really like to change a function name, be sure to keep also the
--  old one running.

-- Usage references:
-- https://longturn.readthedocs.io/en/latest/Contributing/style-guide.html
-- https://luals.github.io/wiki/definition-files
-- https://luals.github.io/wiki/annotations/#documenting-types
-- https://taminomara.github.io/sphinx-lua-ls/index.html#autodoc-directives
-- https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html#rst-primer


--- event is an event type from the E module, for example E.SCRIPT. These
--- correspond to the categories that the client can filter on, and are defined
--- in common/events.cpp. 
---
--- !doctype table
--- @class E
E = {
  TECH_GAIN = 0,                -- Acquired a New Tech
  TECH_LEARNED = 1,             -- Learned a New Tech
  TECH_GOAL = 2,                -- Selected a New Goal
  TECH_LOST = 3,                -- Lost a Tech
  TECH_EMBASSY = 4,             -- Other Player Gained / Lost a Tech
  IMP_BUY = 5,                  -- Bought
  IMP_BUILD = 6,                -- Built
  IMP_AUCTIONED = 7,            -- Forced to Sell
  IMP_AUTO = 8,                 -- New Improvement Selected
  IMP_SOLD = 9,                 -- Sold
  CITY_CANTBUILD = 10,          -- Building Unavailable Item
  CITY_LOST = 11,               -- Captured / Destroyed
  CITY_LOVE = 12,               -- Celebrating
  CITY_DISORDER = 13,           -- Civil Disorder
  CITY_FAMINE = 14,             -- Famine
  CITY_FAMINFEARED = 15,      -- Famine Feared
  CITY_GROWTH = 16,             -- Growth
  CITY_MAY_SOON_GROW = 17,      -- May Soon Grow
  CITY_IMPROVEMENT = 18,        -- Needs Improvement to Grow
  CITY_IMPROVEMENT_BLDG = 19,   -- Needs Improvement to Grow, Being Built
  CITY_NORMAL = 20,              -- Normal
  CITY_NUKED = 21,              -- Nuked
  CITY_CMA_RELEASE = 22,        -- Released from Citizen Governor
  CITY_GRAN_THROTTLE = 23,      -- Suggest Throttling Growth
  CITY_TRANSFER = 24,           -- Transfer
  CITY_BUILD = 25,              -- Was Built
  CITY_PLAGUE = 26,             -- Has Plague
  CITY_RADIUS_SQ = 27,          -- City Map changed
  WORKLIST = 28,                -- Worklist Events
  CITY_PRODUCTION_CHANGED = 29, -- Production Changed
  DISASTER = 30,                -- Disaster
  MY_DIPLOMAT_BRIBE = 31,       -- Bribe
  DIPLOMATIC_INCIDENT = 32,     -- Caused Incident
  MY_DIPLOMAT_ESCAPE = 33,      -- Escape
  MY_DIPLOMAT_EMBASSY = 34,     -- Embassy
  MY_DIPLOMAT_FAILED = 35,      -- Failed
  MY_DIPLOMAT_INCITE = 36,      -- Incite
  MY_DIPLOMAT_POISON = 37,      -- Poison
  MY_DIPLOMAT_SABOTAGE = 38,    -- Sabotage
  MY_DIPLOMAT_THEFT = 39,       -- Theft
  MY_SPY_STEAL_GOLD = 40,       -- Gold Theft
  MY_SPY_STEAL_MAP = 41,        -- Map Theft
  MY_SPY_NUKE = 42,             -- Suitcase Nuke
  ENEMY_DIPLOMAT_BRIBE = 43,    -- Bribe
  ENEMY_DIPLOMAT_EMBASSY = 44,  -- Embassy
  ENEMY_DIPLOMAT_FAILED = 45,   -- Failed
  ENEMY_DIPLOMAT_INCITE = 46,   -- Incite
  ENEMY_DIPLOMAT_POISON = 47,   -- Poison
  ENEMY_DIPLOMAT_SABOTAGE = 48, -- Sabotage
  ENEMY_DIPLOMAT_THEFT = 49,    -- Theft
  ENEMY_SPY_STEAL_GOLD = 50,    -- Gold Theft
  ENEMY_SPY_STEAL_MAP = 51,     -- Map Theft
  ENEMY_SPY_NUKE = 52,          -- Suitcase Nuke
  GLOBAL_ECO = 53,              -- Eco-Disaster
  NUKE = 54,                    -- Nuke Detonated
  HUT_BARB = 55,                -- Barbarians in a Hut
  HUT_CITY = 56,                -- City Founded from a Hut
  HUT_GOLD = 57,                -- Gold Found in a Hut
  HUT_BARB_KILLED = 58,         -- Killed by Barbarians in a Hut
  HUT_MERC = 59,                -- Mercenaries Found in a Hut
  HUT_SETTLER = 60,             -- Settlers Found in a Hut
  HUT_TECH = 61,                -- Tech Found in a Hut
  HUT_BARB_CITY_NEAR = 62,      -- Unit Spared by Barbarians
  ACHIEVEMENT = 63,             -- Achievements
  UPRISING = 64,                -- Barbarian Uprising
  CIVIL_WAR = 65,               -- Civil War
  ANARCHY = 66,                 -- Collapse to Anarchy
  FIRST_CONTACT = 67,           -- First Contact
  NEW_GOVERNMENT = 68,          -- Learned New Government
  LOW_ON_FUNDS = 69,            -- Low Funds
  POLLUTION = 70,               -- Pollution
  REVOLT_DONE = 71,             -- Revolution Ended
  REVOLT_START = 72,            -- Revolution Started
  SPACESHIP = 73,               -- Spaceship Events
  TREATY_ALLIANCE = 74,         -- Alliance
  TREATY_BROKEN = 75,           -- Broken
  TREATY_CEASEFIRE = 76,        -- Cease-fire
  TREATY_EMBASSY = 77,          -- Embassy
  TREATY_PEACE = 78,            -- Peace
  TREATY_SHARED_VISION = 79,    -- Shared Vision
  UNIT_LOST_ATT = 80,           -- Attack Failed
  UNIT_TIATT = 81,            -- Attack Tied
  UNIT_WIN_ATT = 82,            -- Attack Succeeded
  UNIT_BOMB_ATT = 83,           -- Attacker Bombarding
  UNIT_BUY = 84,                -- Bought
  UNIT_BUILT = 85,              -- Built
  UNIT_LOST_DEF = 86,           -- Defender Destroyed
  UNIT_TIDEF = 87,            -- Defender Tied
  UNIT_WIN_DEF = 88,            -- Defender Survived
  UNIT_BOMB_DEF = 89,           -- Defender Bombarded
  UNIT_BECAMVET = 90,         -- Promoted to Veteran
  UNIT_LOST_MISC = 91,          -- Lost Outside Battle
  UNIT_UPGRADED = 92,           -- Production Upgraded
  UNIT_RELOCATED = 93,          -- Relocated
  UNIT_ORDERS = 94,             -- Orders / Goto Events
  UNIT_BUILT_POP_COST = 95,     -- Built Unit with Population Cost
  UNIT_WAS_EXPELLED = 96,       -- Was Expelled
  UNIT_DID_EXPEL = 97,          -- Did Expel
  UNIT_ACTION_FAILED = 98,      -- Action Failed
  UNIT_WAKE = 99,               -- Sentried Units Awaken
  VOTNEW = 100,               -- New Vote
  VOTRESOLVED = 101,          -- Vote Resolved
  VOTABORTED = 102,           -- Vote Canceled
  WONDER_BUILD = 103,           -- Finished
  WONDER_OBSOLETE = 104,        -- Made Obsolete
  WONDER_STARTED = 105,         -- Started
  WONDER_STOPPED = 106,         -- Stopped
  WONDER_WILL_BBUILT = 107,   -- Will Finish Next Turn
  AI_DEBUG = 108,               -- AI Debug Messages
  BROADCAST_REPORT = 109,       -- Broadcast Report
  CARAVAN_ACTION = 110,         -- Caravan Actions
  CHAT_ERROR = 111,             -- Chat Error Messages
  CHAT_MSG = 112,               -- Chat Messages
  CONNECTION = 113,             -- Connect / Disconnect Messages
  DIPLOMACY = 114,              -- Diplomatic Message
  BAD_COMMAND = 115,            -- Error Message from Bad Command
  GAMEND = 116,               -- Game Ended
  GAMSTART = 117,             -- Game Started
  NATION_SELECTED = 118,        -- Nation Selected
  DESTROYED = 119,              -- Player Destroyed
  REPORT = 120,                 -- Report
  LOG_FATAL = 121,              -- Server Aborting
  LOG_ERROR = 122,              -- Server Problems
  MESSAGWALL = 123,           -- Message from Server Operator
  SETTING = 124,                -- Server Settings Changed
  TURN_BELL = 125,              -- Turn Bell
  SCRIPT = 126,                 -- Scenario / Ruleset Script Message
  NEXT_YEAR = 127,              -- Year Advance
  DEPRECATION_WARNING = 128,    -- Deprecated Modpack Syntax Warnings
  SPONTANEOUS_EXTRA = 129,      -- Extra Appears / Disappears
  UNIT_ILLEGAL_ACTION = 130,    -- Unit Illegal Action
  UNIT_ESCAPED = 131,           -- Unit Escaped
  BEGINNER_HELP = 132,          -- Help for Beginners
  MY_UNIT_DID_HEAL = 133,       -- Unit Did Heal
  MY_UNIT_WAS_HEALED = 134,     -- Unit Was Healed
  MULTIPLIER = 135,             -- Multiplier Changed
  UNIT_ACTION_ACTOR_SUCCESS = 136, -- Your Unit Did
  UNIT_ACTION_ACTOR_FAILURE = 137, -- Your Unit Failed
  UNIT_ACTION_TARGET_HOSTILE = 138, -- Unit Did to You
  UNIT_ACTION_TARGET_OTHER = 139, -- Unit Did
}

