// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

void dai_do_first_activities(struct ai_type *ait, struct player *pplayer);
void dai_do_last_activities(struct ai_type *ait, struct player *pplayer);

void dai_calc_data(const struct player *pplayer, int *trade, int *expenses,
                   int *income);
