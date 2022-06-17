// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

#include "fc_types.h"

struct city;

#define MAX_CITY_NATIONALITIES MIN(MAX_NUM_PLAYER_SLOTS, MAX_CITY_SIZE)

struct citizens_reduction {
  struct player_slot *pslot;
  citizens change;
};

void citizens_update(struct city *pcity, struct player *plr);
void citizens_convert(struct city *pcity);
void citizens_convert_conquest(struct city *pcity);
struct player *citizens_unit_nationality(const struct city *pcity,
                                         int pop_cost,
                                         struct citizens_reduction *pchange);
void citizens_reduction_apply(struct city *pcity,
                              const struct citizens_reduction *pchange);

void citizens_print(const struct city *pcity);
