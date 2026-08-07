// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

struct section_file;
struct connection;
struct conn_list;

void init_new_game();
void send_year_to_clients();
void send_game_info(struct conn_list *dest);

void send_scenario_info(struct conn_list *dest);
void send_scenario_description(struct conn_list *dest);

enum unit_role_id crole_to_role_id(char crole);
struct unit_type *crole_to_unit_type(char crole, struct player *pplayer);

int update_timeout();
void increase_timeout_because_unit_moved();

const char *new_challenge_filename(struct connection *pc);
