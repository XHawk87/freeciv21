// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

// common
#include "fc_types.h"

#pragma once

// How many turns after latest combat war mood lasts
#define WAR_MOOD_LASTS 10

enum mood_type player_mood(struct player *pplayer);
