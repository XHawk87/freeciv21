// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

struct adv_choice;
struct city;
struct player;
struct unit;

void dai_manage_paratrooper(struct ai_type *ait, struct player *pplayer,
                            struct unit *punit);
void dai_choose_paratrooper(struct ai_type *ait, struct player *pplayer,
                            struct city *pcity, struct adv_choice *choice,
                            bool allow_gold_upkeep);
