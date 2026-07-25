// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// See handicap_desc() for what these do.
enum handicap_type {
  H_DIPLOMAT = 0,
  H_AWAY,
  H_LIMITEDHUTS,
  H_DEFENSIVE,
  H_EXPERIMENTAL,
  H_RATES,
  H_TARGETS,
  H_HUTS,
  H_FOG,
  H_NOPLANES,
  H_MAP,
  H_DIPLOMACY,
  H_REVOLUTION,
  H_EXPANSION,
  H_DANGER,
  H_CEASEFIRE,
  H_NOBRIBE_WF,
  H_PRODCHGPEN,
  H_LAST
};
class QBitArray;

void handicaps_init(struct player *pplayer);
void handicaps_close(struct player *pplayer);

void handicaps_set(struct player *pplayer, QBitArray *handicaps);
bool has_handicap(const struct player *pplayer, enum handicap_type htype);

const char *handicap_desc(enum handicap_type htype, bool *inverted);
