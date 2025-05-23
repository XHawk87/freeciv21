// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

// self
#include "achievements.h"

// utility
#include "bitvector.h"
#include "fcintl.h"
#include "log.h"
#include "rand.h"
#include "shared.h"
#include "support.h"

// common
#include "citizens.h"
#include "city.h"
#include "culture.h"
#include "fc_types.h"
#include "game.h"
#include "map.h"
#include "name_translation.h"
#include "player.h"
#include "spaceship.h"
#include "terrain.h"
#include "tile.h"

// Qt
#include <QtLogging> // qDebug, qWarning, qCricital, etc

// std
#include <vector> // std:vector

static struct achievement achievements[MAX_ACHIEVEMENT_TYPES];

/**
   Initialize achievements.
 */
void achievements_init()
{
  int i;

  for (i = 0; i < ARRAY_SIZE(achievements); i++) {
    achievements[i].id = i;
    achievements[i].ruledit_disabled = false;
    achievements[i].first = nullptr;
    achievements[i].value = 0;
    achievements[i].culture = 0;
    BV_CLR_ALL(achievements[i].achievers);
    achievements[i].first_msg = nullptr;
    achievements[i].cons_msg = nullptr;
  }
}

/**
   Free the memory associated with achievements
 */
void achievements_free()
{
  int i;

  for (i = 0; i < ARRAY_SIZE(achievements); i++) {
    delete[] achievements[i].first_msg;
    delete[] achievements[i].cons_msg;
  }
}

/**
   Return the achievement id.
 */
int achievement_number(const struct achievement *pach)
{
  fc_assert_ret_val(nullptr != pach, 0);

  return pach->id;
}

/**
   Return the achievement index.
 */
int achievement_index(const struct achievement *pach)
{
  fc_assert_ret_val(nullptr != pach, 0);

  return pach - achievements;
}

/**
   Return achievements of given id.
 */
struct achievement *achievement_by_number(int id)
{
  fc_assert_ret_val(id >= 0 && id < game.control.num_achievement_types,
                    nullptr);

  return &achievements[id];
}

/**
   Return translated name of this achievement type.
 */
const char *achievement_name_translation(struct achievement *pach)
{
  return name_translation_get(&pach->name);
}

/**
   Return untranslated name of this achievement type.
 */
const char *achievement_rule_name(struct achievement *pach)
{
  return rule_name_get(&pach->name);
}

/**
   Returns achievement matching rule name or nullptr if there is no
   achievement with such name.
 */
struct achievement *achievement_by_rule_name(const char *name)
{
  const char *qs = Qn_(name);

  achievements_iterate(pach)
  {
    if (!fc_strcasecmp(achievement_rule_name(pach), qs)) {
      return pach;
    }
  }
  achievements_iterate_end;

  return nullptr;
}

/**
   Check if some player has now achieved the achievement and return the
 player in question.
 */
struct player *achievement_plr(struct achievement *ach,
                               struct player_list *achievers)
{
  struct player *credited = nullptr;

  players_iterate(pplayer)
  {
    if (achievement_check(ach, pplayer)) {
      if (!ach->unique) {
        pplayer->history += ach->culture;
        BV_SET(ach->achievers, player_index(pplayer));
      }
      player_list_append(achievers, pplayer);
    }
  }
  players_iterate_end;

  if (ach->first != nullptr) {
    // Already have first one credited.
    return nullptr;
  }

  if (player_list_size(achievers) > 0) {
    /* If multiple players achieved at the same turn, randomly select one
     * as the one who won the race. */
    credited =
        player_list_get(achievers, fc_rand(player_list_size(achievers)));

    ach->first = credited;

    if (ach->unique) {
      // For !ach->unique achievements culture was already added above.
      credited->history += ach->culture;
    }

    // Mark the selected player as the only one having the achievement
    BV_SET(ach->achievers, player_index(credited));
  }

  return credited;
}

/**
   Check if player has now achieved the achievement.
 */
bool achievement_check(struct achievement *ach, struct player *pplayer)
{
  if ((ach->unique && ach->first != nullptr)
      || (BV_ISSET(ach->achievers, player_index(pplayer)))) {
    // It was already achieved
    return false;
  }

  switch (ach->type) {
  case ACHIEVEMENT_SPACESHIP:
    return pplayer->spaceship.state == SSHIP_LAUNCHED;
  case ACHIEVEMENT_MAP: {
    int max_unknown;
    int required;
    int total;
    int known = 0;
    int unknown = 0;

    /* We calculate max_unknown first for getting the
     * rounding correctly.
     * Consider 50 tile map from which we want 25% known.
     * 50 * 25% = 12.5. Would we round that number of tiles
     * down, we would get < 25% that's minimum requirement.
     * Instead we round down (50 - 12.5 = 37.5) -> 37 and then
     * get the minimum number of full tiles as 50 - 37 = 13. */
    total = map_num_tiles();
    max_unknown = (total * (100 - ach->value)) / 100;
    required = total - max_unknown;

    whole_map_iterate(&(wld.map), ptile)
    {
      bool this_is_known = false;

      if (is_server()) {
        if (pplayer->tile_known->at(tile_index(ptile))) {
          this_is_known = true;
        }
      } else {
        // Client
        if (ptile->terrain != T_UNKNOWN) {
          this_is_known = true;
        }
      }

      if (this_is_known) {
        known++;
        if (known >= required) {
          return true;
        }
      } else {
        unknown++;
        if (unknown >= max_unknown) {
          return false;
        }
      }
    }
    whole_map_iterate_end;
  }

    return false;
  case ACHIEVEMENT_MULTICULTURAL: {
    bv_player seen_citizens;
    int count = 0;

    BV_CLR_ALL(seen_citizens);

    city_list_iterate(pplayer->cities, pcity)
    {
      citizens_iterate(pcity, pslot, pnat)
      {
        int idx = player_index(player_slot_get_player(pslot));

        if (!BV_ISSET(seen_citizens, idx)) {
          BV_SET(seen_citizens, idx);
          count++;
          if (count >= ach->value) {
            // There's at least value different nationalities.
            return true;
          }
        }
      }
      citizens_iterate_end;
    }
    city_list_iterate_end;
  }

    return false;
  case ACHIEVEMENT_CULTURED_CITY:
    city_list_iterate(pplayer->cities, pcity)
    {
      if (city_culture(pcity) >= ach->value) {
        return true;
      }
    }
    city_list_iterate_end;

    return false;
  case ACHIEVEMENT_CULTURED_NATION:
    if (player_culture(pplayer) >= ach->value) {
      return true;
    }

    return false;
  case ACHIEVEMENT_LUCKY:
    return (static_cast<int>(fc_rand(10000)) < ach->value);
  case ACHIEVEMENT_HUTS:
    return pplayer->server.huts >= ach->value;
  case ACHIEVEMENT_METROPOLIS:
    city_list_iterate(pplayer->cities, pcity)
    {
      if (city_size_get(pcity) >= ach->value) {
        return true;
      }
    }
    city_list_iterate_end;

    return false;
  case ACHIEVEMENT_LITERATE:
    return get_literacy(pplayer) >= ach->value;
  case ACHIEVEMENT_LAND_AHOY: {
    std::vector<bool> seen(wld.map.num_continents);
    int count = 0;

    whole_map_iterate(&(wld.map), ptile)
    {
      bool this_is_known = false;

      if (is_server()) {
        if (pplayer->tile_known->at(tile_index(ptile))) {
          this_is_known = true;
        }
      } else {
        // Client
        if (ptile->terrain != T_UNKNOWN) {
          this_is_known = true;
        }
      }

      if (this_is_known) {
        /* FIXME: This makes the assumption that fogged tiles belonged
         *        to their current continent when they were last seen. */
        if (ptile->continent > 0 && !seen[ptile->continent - 1]) {
          if (++count >= ach->value) {
            return true;
          }
          seen[ptile->continent - 1] = true;
        }
      }
    }
    whole_map_iterate_end;

    return false;
  }
  case ACHIEVEMENT_COUNT:
    break;
  }

  qCritical("achievement_check(): Illegal achievement type %d", ach->type);

  return false;
}

/**
   Return message to send to first player gaining the achievement.
 */
const char *achievement_first_msg(struct achievement *pach)
{
  fc_assert(pach->first_msg != nullptr);

  return _(pach->first_msg);
}

/**
   Return message to send to other players gaining the achievement.
 */
const char *achievement_later_msg(struct achievement *pach)
{
  fc_assert(pach->cons_msg != nullptr);

  return _(pach->cons_msg);
}

/**
   Has the given player got the achievement?
 */
bool achievement_player_has(const struct achievement *pach,
                            const struct player *pplayer)
{
  if (pplayer == nullptr) {
    return false;
  }

  return BV_ISSET(pach->achievers, player_index(pplayer));
}

/**
   Has anybody got the achievement?
 */
bool achievement_claimed(const struct achievement *pach)
{
  return pach->first != nullptr;
}

/**
   Literacy score calculated one way. See also get_literacy2() for
   alternative way.
 */
int get_literacy(const struct player *pplayer)
{
  int pop = civ_population(pplayer);

  if (pop <= 0) {
    return 0;
  } else if (pop >= 10000) {
    return pplayer->score.literacy / (pop / 100);
  } else {
    return (pplayer->score.literacy * 100) / pop;
  }
}
