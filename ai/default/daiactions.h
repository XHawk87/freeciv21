// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "actions.h"
#include "fc_types.h"

adv_want dai_action_value_unit_vs_city(struct action *paction,
                                       struct unit *actor_unit,
                                       struct city *target_city,
                                       int sub_tgt_id, int count_tech);

int dai_action_choose_sub_tgt_unit_vs_city(struct action *paction,
                                           struct unit *actor_unit,
                                           struct city *target_city);
