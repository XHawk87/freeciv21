// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

// self
#include "aitraits.h"

// utility
#include "rand.h"
#include "shared.h"

// common
#include "fc_types.h"
#include "game.h"
#include "nation.h"
#include "player.h"
#include "traits.h"

// std
#include <vector> // std:vector

/**
   Initialize ai traits for player
 */
void ai_traits_init(struct player *pplayer)
{
  enum trait tr;

  pplayer->ai_common.traits = std::vector<ai_trait>(TRAIT_COUNT);

  for (tr = trait_begin(); tr != trait_end(); tr = trait_next(tr)) {
    int min = pplayer->nation->server.traits[tr].min;
    int max = pplayer->nation->server.traits[tr].max;

    switch (game.server.trait_dist) {
    case TDM_FIXED:
      pplayer->ai_common.traits[tr].val =
          pplayer->nation->server.traits[tr].fixed;
      break;
    case TDM_EVEN:
      pplayer->ai_common.traits[tr].val = fc_rand(max + 1 - min) + min;
      break;
    }
    pplayer->ai_common.traits[tr].mod = 0;
  }
}

/**
   Free resources associated with player ai traits.
 */
void ai_traits_close(struct player *pplayer)
{
  pplayer->ai_common.traits.clear();
}

/**
   Get current value of player trait
 */
int ai_trait_get_value(enum trait tr, struct player *pplayer)
{
  int val =
      pplayer->ai_common.traits[tr].val + pplayer->ai_common.traits[tr].mod;

  /* Clip so that value is at least 1, and maximum is
   * TRAIT_DEFAULT_VALUE as many times as TRAIT_DEFAULT value is
   * minimum value of 1 ->
   * minimum is default / TRAIT_DEFAULT_VALUE,
   * maximum is default * TRAIT_DEFAULT_VALUE */
  val = CLIP(1, val, TRAIT_MAX_VALUE);

  return val;
}
