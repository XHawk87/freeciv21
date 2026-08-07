// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

bool diplomat_embassy(struct player *pplayer, struct unit *pdiplomat,
                      struct city *pcity, const struct action *paction);
bool diplomat_investigate(struct player *pplayer, struct unit *pdiplomat,
                          struct city *pcity, const struct action *paction);
void spy_send_sabotage_list(struct connection *pc, struct unit *pdiplomat,
                            struct city *pcity, const struct action *paction,
                            bool disturb_player);
bool spy_poison(struct player *pplayer, struct unit *pdiplomat,
                struct city *pcity, const struct action *paction);
bool spy_spread_plague(struct player *act_player, struct unit *act_unit,
                       struct city *tgt_city, const struct action *paction);
bool spy_sabotage_unit(struct player *pplayer, struct unit *pdiplomat,
                       struct unit *pvictim, const struct action *paction);
bool diplomat_bribe(struct player *pplayer, struct unit *pdiplomat,
                    struct unit *pvictim, const struct action *paction);
bool spy_attack(struct player *act_player, struct unit *act_unit,
                struct tile *tgt_tile, const struct action *paction);
int diplomats_unignored_tech_stealings(struct unit *pdiplomat,
                                       struct city *pcity);
bool diplomat_get_tech(struct player *pplayer, struct unit *pdiplomat,
                       struct city *pcity, int technology,
                       const struct action *paction);
bool diplomat_incite(struct player *pplayer, struct unit *pdiplomat,
                     struct city *pcity, const struct action *paction);
bool diplomat_sabotage(struct player *pplayer, struct unit *pdiplomat,
                       struct city *pcity, Impr_type_id improvement,
                       const struct action *paction);
bool spy_steal_gold(struct player *act_player, struct unit *act_unit,
                    struct city *tgt_city, const struct action *paction);
bool spy_steal_some_maps(struct player *act_player, struct unit *act_unit,
                         struct city *tgt_city,
                         const struct action *paction);
bool spy_nuke_city(struct player *act_player, struct unit *act_unit,
                   struct city *tgt_city, const struct action *paction);

int count_diplomats_on_tile(struct tile *ptile);
