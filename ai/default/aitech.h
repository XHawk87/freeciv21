// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"
#include "unittype.h"

void dai_manage_tech(struct ai_type *ait, struct player *pplayer);
void dai_clear_tech_wants(struct ai_type *ait, struct player *pplayer);
struct unit_type *dai_wants_role_unit(struct ai_type *ait,
                                      struct player *pplayer,
                                      struct city *pcity, int role,
                                      int want);
struct unit_type *dai_wants_defender_against(struct ai_type *ait,
                                             struct player *pplayer,
                                             struct city *pcity,
                                             const struct unit_type *att,
                                             int want);
