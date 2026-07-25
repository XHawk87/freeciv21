// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "ai.h"
#include "city.h"
#include "fc_types.h"

struct ai_plr;
struct tile_data_cache;

void dai_auto_settler_init(struct ai_plr *ai);
void dai_auto_settler_free(struct ai_plr *ai);

void dai_auto_settler_reset(struct ai_type *ait, struct player *pplayer);
void dai_auto_settler_run(struct ai_type *ait, struct player *pplayer,
                          struct unit *punit, struct settlermap *state);
void dai_auto_settler_cont(struct ai_type *ait, struct player *pplayer,
                           struct unit *punit, struct settlermap *state);

void contemplate_new_city(struct ai_type *ait, struct city *pcity);
