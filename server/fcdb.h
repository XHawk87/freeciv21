// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

bool fcdb_init(const char *conf_file);
const char *fcdb_option_get(const char *type);
void fcdb_free();
