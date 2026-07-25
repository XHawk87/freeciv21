// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

adv_want dai_effect_value(struct player *pplayer, struct government *gov,
                          const struct adv_data *adv,
                          const struct city *pcity, const bool capital,
                          int turns, const struct effect *peffect,
                          const int c, const int nplayers);

adv_want dai_content_effect_value(const struct player *pplayer,
                                  const struct city *pcity, int amount,
                                  int num_cities, int happiness_step);

bool dai_can_requirement_be_met_in_city(const struct requirement *preq,
                                        const struct player *pplayer,
                                        const struct city *pcity);
