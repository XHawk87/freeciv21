// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

// self
#include "mood.h"

// common
#include "fc_types.h"
#include "game.h"
#include "player.h"

/**
   What is the player mood?
 */
enum mood_type player_mood(struct player *pplayer)
{
  if (pplayer->last_war_action >= 0
      && pplayer->last_war_action + WAR_MOOD_LASTS >= game.info.turn) {
    players_iterate(other)
    {
      struct player_diplstate *us, *them;

      us = player_diplstate_get(pplayer, other);
      them = player_diplstate_get(other, pplayer);

      if (us->type == DS_WAR || us->has_reason_to_cancel > 0
          || them->has_reason_to_cancel > 0) {
        return MOOD_COMBAT;
      }
    }
    players_iterate_end;
  }

  return MOOD_PEACEFUL;
}
