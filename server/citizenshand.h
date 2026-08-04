// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

struct city;

void citizens_update(struct city *pcity, struct player *plr);
void citizens_convert(struct city *pcity);
void citizens_convert_conquest(struct city *pcity);

void citizens_print(const struct city *pcity);
