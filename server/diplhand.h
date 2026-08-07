// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// common
#include "fc_types.h"

struct Treaty;
struct packet_diplomacy_info;
struct connection;

#define SPECLIST_TAG treaty
#define SPECLIST_TYPE struct Treaty
#include "speclist.h"

// FIXME: Should this be put in a ruleset somewhere?
const int TURNS_LEFT = 16;
const int TURNS_EXTEND_CEASEFIRE = 1;

#define treaty_list_iterate(list, p)                                        \
  TYPED_LIST_ITERATE(struct Treaty, list, p)
#define treaty_list_iterate_end LIST_ITERATE_END

void establish_embassy(struct player *pplayer, struct player *aplayer);

void diplhand_init();
void diplhand_free();
void free_treaties();

struct Treaty *find_treaty(struct player *plr0, struct player *plr1);

void send_diplomatic_meetings(struct connection *dest);
void cancel_all_meetings(struct player *pplayer);
void reject_all_treaties(struct player *pplayer);

struct treaty_list *get_all_treaties();
