// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

void dai_manage_diplomat(struct ai_type *ait, struct player *pplayer,
                         struct unit *punit);
void dai_choose_diplomat_defensive(struct ai_type *ait,
                                   struct player *pplayer,
                                   struct city *pcity,
                                   struct adv_choice *choice, int def);
void dai_choose_diplomat_offensive(struct ai_type *ait,
                                   struct player *pplayer,
                                   struct city *pcity,
                                   struct adv_choice *choice);
