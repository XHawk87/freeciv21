// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

struct connection;
struct conn_list;

void really_handle_city_sell(struct player *pplayer, struct city *pcity,
                             struct impr_type *pimprove);
void really_handle_city_buy(struct player *pplayer, struct city *pcity);
