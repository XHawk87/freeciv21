// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

#define MIN_UNREST_DIST 5
#define MAX_UNREST_DIST 8

#define UPRISE_CIV_SIZE 10

#define MAP_FACTOR 2000 // adjust this to get a good uprising frequency

#define BARBARIAN_MIN_LIFESPAN 5

bool unleash_barbarians(struct tile *ptile);
void summon_barbarians();
bool is_land_barbarian(struct player *pplayer);
bool is_sea_barbarian(struct player *pplayer);

struct player *create_barbarian_player(enum barbarian_type type);
