// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

// self
#include "fcdb.h"

// utility
#include "fcintl.h"
#include "log.h"
#include "registry.h"
#include "registry_ini.h"
#include "section_file.h"
#include "support.h"

// server
#include "script_fcdb.h"

// Qt
#include <QHash>
#include <QString>
#include <QtLogging> // qInfo, qDebug, qWarning, qCritical

// std
#include <cstring> // str*, mem*
#include <utility> // std::as_const

struct fcdb_option {
  char *value;
};

QHash<QString, fcdb_option *> fcdb_config;

static bool fcdb_set_option(const char *key, const char *value);
static bool fcdb_load_config(const char *filename);

/**
   Set one fcdb option (or delete it if value == nullptr).
   Replaces any previous setting.
 */
static bool fcdb_set_option(const char *key, const char *value)
{
  struct fcdb_option *oldopt = nullptr;
  bool removed;

  if (value != nullptr) {
    auto newopt = new fcdb_option;

    newopt->value = fc_strdup(value);

    removed = fcdb_config.contains(key);
    if (removed) {
      oldopt = fcdb_config.value(key);
    }
    fcdb_config[key] = newopt;
  } else {
    removed = fcdb_config.contains(key);
    if (removed) {
      oldopt = fcdb_config.take(key);
    }
  }

  if (removed) {
    /* Overwritten/removed an existing value */
    fc_assert_ret_val(oldopt != nullptr, false);
    delete[] oldopt->value;
    delete oldopt;
    oldopt = nullptr;
  }

  return true;
}

/**
   Load fcdb configuration from file.
   We deliberately don't search datadirs for filename, as we don't want this
   overridden by modpacks etc.
 */
static bool fcdb_load_config(const char *filename)
{
  struct section_file *secfile;

  fc_assert_ret_val(nullptr != filename, false);

  if (!(secfile = secfile_load(filename, false))) {
    qCritical(_("Cannot load fcdb config file '%s':\n%s"), filename,
              secfile_error());
    return false;
  }

  entry_list_iterate(
      section_entries(secfile_section_by_name(secfile, "fcdb")), pentry)
  {
    if (entry_type_get(pentry) == ENTRY_STR) {
      const char *value;
      bool entry_str_get_success = entry_str_get(pentry, &value);

      fc_assert(entry_str_get_success);
      fcdb_set_option(entry_name(pentry), value);
    } else {
      qCritical("Value for '%s' in '%s' is not of string type, ignoring",
                entry_name(pentry), filename);
    }
  }
  entry_list_iterate_end;

  /* FIXME: we could arrange to call secfile_check_unused() and have it
   * complain about unused entries (e.g. those not in [fcdb]). */
  secfile_destroy(secfile);

  return true;
}

/**
   Initialize freeciv database system
 */
bool fcdb_init(const char *conf_file)
{
  if (conf_file && strcmp(conf_file, "-")) {
    if (!fcdb_load_config(conf_file)) {
      return false;
    }
  } else {
    log_debug("No fcdb config file.");
  }

  return script_fcdb_init(nullptr);
}

/**
   Return the selected fcdb config value.
 */
const char *fcdb_option_get(const char *type)
{
  if (fcdb_config.contains(type)) {
    return fcdb_config[type]->value;
  } else {
    return nullptr;
  }
}

/**
   Free resources allocated by fcdb system.
 */
void fcdb_free(void)
{
  script_fcdb_free();

  for (auto popt : std::as_const(fcdb_config)) {
    // Dangling pointers freed below
    delete[] popt->value;
    delete popt;
    popt = nullptr;
  }
  fcdb_config.clear();
}
