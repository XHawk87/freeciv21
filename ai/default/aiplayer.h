// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// utility
#include "section_file.h"

// common
#include "city.h"
#include "player.h"
#include "unit.h"

struct player;
struct ai_plr;

void dai_player_alloc(struct ai_type *ait, struct player *pplayer);
void dai_player_free(struct ai_type *ait, struct player *pplayer);
void dai_player_save_relations(struct ai_type *ait, const char *aitstr,
                               struct player *pplayer, struct player *other,
                               struct section_file *file, int plrno);
void dai_player_load_relations(struct ai_type *ait, const char *aitstr,
                               struct player *pplayer, struct player *other,
                               const struct section_file *file, int plrno);

void dai_player_copy(struct ai_type *ait, struct player *original,
                     struct player *created);
void dai_gained_control(struct ai_type *ait, struct player *pplayer);

static inline struct ai_city *def_ai_city_data(const struct city *pcity,
                                               struct ai_type *deftype)
{
  return static_cast<struct ai_city *>(city_ai_data(pcity, deftype));
}

static inline struct unit_ai *def_ai_unit_data(const struct unit *punit,
                                               struct ai_type *deftype)
{
  return static_cast<struct unit_ai *>(unit_ai_data(punit, deftype));
}

static inline struct ai_plr *def_ai_player_data(const struct player *pplayer,
                                                struct ai_type *deftype)
{
  return static_cast<struct ai_plr *>(player_ai_data(pplayer, deftype));
}

struct dai_private_data {
  bool contemplace_workers;
};
