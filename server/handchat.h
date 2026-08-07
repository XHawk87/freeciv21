// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

struct connection;

// This function is called from the generated code in generate_packets.py
void handle_chat_msg_req(struct connection *pc, const char *message);
