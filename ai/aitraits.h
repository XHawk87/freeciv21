// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

int ai_trait_get_value(enum trait tr, struct player *pplayer);

void ai_traits_init(struct player *pplayer);
void ai_traits_close(struct player *pplayer);
