// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

struct conn_list;

void edithand_init();
void edithand_free();

void edithand_send_initial_packets(struct conn_list *dest);
