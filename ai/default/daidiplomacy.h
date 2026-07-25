// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "ai.h"
#include "fc_types.h"

struct Treaty;
struct Clause;

void dai_diplomacy_begin_new_phase(struct ai_type *ait,
                                   struct player *pplayer);
void dai_diplomacy_actions(struct ai_type *ait, struct player *pplayer);

void dai_treaty_evaluate(struct ai_type *ait, struct player *pplayer,
                         struct player *aplayer, struct Treaty *ptreaty);
void dai_treaty_accepted(struct ai_type *ait, struct player *pplayer,
                         struct player *aplayer, struct Treaty *ptreaty);

void dai_incident(struct ai_type *ait, enum incident_type type,
                  enum casus_belli_range scope, const struct action *paction,
                  struct player *receiver, struct player *violator,
                  struct player *victim);

bool dai_on_war_footing(struct ai_type *ait, struct player *pplayer);

void dai_diplomacy_first_contact(struct ai_type *ait, struct player *pplayer,
                                 struct player *aplayer);
