// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "ai.h"
#include "fc_types.h"

void ai_init();

bool load_ai_module(const char *modname);

const char *default_ai_type_name();

void call_incident(enum incident_type type, enum casus_belli_range scope,
                   const struct action *paction, struct player *violator,
                   struct player *victim);
void call_ai_refresh();
