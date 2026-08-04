// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

struct server_connection;

bool auth_user(server_connection *pconn, char *username);
void auth_process_status(server_connection *pconn);
bool auth_handle_reply(server_connection *pconn, char *password);

const char *auth_get_username(server_connection *pconn);
const char *auth_get_ipaddr(server_connection *pconn);
