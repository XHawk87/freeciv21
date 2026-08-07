// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// utility
#include "support.h" // bool type

// Forward declarations
class QString;

#define DEFAULT_META_SERVER_NO_SEND true
#define DEFAULT_META_SERVER_ADDR FREECIV_META_URL
#define METASERVER_REFRESH_INTERVAL (3 * 60)
#define METASERVER_MIN_UPDATE_INTERVAL 7 // not too short, not too long

enum meta_flag { META_INFO, META_REFRESH, META_GOODBYE };

const char *default_meta_patches_string();
const char *default_meta_message_string();

const char *get_meta_patches_string();
const char *get_meta_message_string();
const char *get_user_meta_message_string();

void maybe_automatic_meta_message(const char *automatic);

void set_meta_patches_string(const char *string);
void set_meta_message_string(const char *string);
void set_user_meta_message_string(const char *string);

QString meta_addr_port();

void server_close_meta();
bool server_open_meta(bool persistent);
bool is_metaserver_open();

bool send_server_info_to_metaserver(enum meta_flag flag);
