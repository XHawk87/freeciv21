// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

struct adv_choice *domestic_advisor_choose_build(struct ai_type *ait,
                                                 struct player *pplayer,
                                                 struct city *pcity);

void dai_wonder_city_distance(struct ai_type *ait, struct player *pplayer,
                              struct adv_data *adv);
