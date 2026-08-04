// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

// std
#include <memory> // std::unique_ptr

struct conn_list;
struct cm_result;

bool city_refresh(struct city *pcity); // call if city has changed
void city_refresh_for_player(struct player *pplayer); /* tax/govt changed */

void city_refresh_queue_add(struct city *pcity);
void city_refresh_queue_processing();

void auto_arrange_workers(struct city *pcity); // will arrange the workers
void apply_cmresult_to_city(struct city *pcity,
                            const std::unique_ptr<cm_result> &cmr);

bool city_change_size(struct city *pcity, citizens new_size,
                      struct player *nationality, const char *reason);
bool city_reduce_size(struct city *pcity, citizens pop_loss,
                      struct player *destroyer, const char *reason);
void city_repair_size(struct city *pcity, int change);

bool city_empty_food_stock(struct city *pcity);

void send_city_turn_notifications(struct connection *pconn);
void update_city_activities(struct player *pplayer);
int city_incite_cost(struct player *pplayer, struct city *pcity);
void remove_obsolete_buildings_city(struct city *pcity, bool refresh);
void remove_obsolete_buildings(struct player *pplayer);

void choose_build_target(struct player *pplayer, struct city *pcity);

void nullify_prechange_production(struct city *pcity);

bool check_city_migrations();

void check_disasters();

void city_style_refresh(struct city *pcity);
