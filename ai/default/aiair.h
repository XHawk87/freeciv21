// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

void dai_manage_airunit(struct ai_type *ait, struct player *pplayer,
                        struct unit *punit);
bool dai_choose_attacker_air(struct ai_type *ait, struct player *pplayer,
                             struct city *pcity, struct adv_choice *choice,
                             bool allow_gold_upkeep);
