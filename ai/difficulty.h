// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

void set_ai_level_directer(struct player *pplayer, enum ai_level level);

char *ai_level_help(const char *cmdname);

bool ai_fuzzy(const struct player *pplayer, bool normal_decision);
