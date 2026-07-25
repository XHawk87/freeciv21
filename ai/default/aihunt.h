// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

void dai_hunter_choice(struct ai_type *ait, struct player *pplayer,
                       struct city *pcity, struct adv_choice *choice,
                       bool allow_gold_upkeep);
bool dai_hunter_qualify(struct player *pplayer, struct unit *punit);
int dai_hunter_manage(struct ai_type *ait, struct player *pplayer,
                      struct unit *punit);
