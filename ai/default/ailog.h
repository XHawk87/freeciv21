// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// utility
#include "support.h"

// common
#include "city.h"
#include "tech.h"
#include "unit.h"

// ai
#include "classicai.h"

// Qt
#include <QLoggingCategory>
#include <QString>
#include <QStringLiteral>
#include <QtGlobal> // qUtf8Printable

Q_DECLARE_LOGGING_CATEGORY(ai_category)

struct player;

void dai_city_log(struct ai_type *ait, char *buffer, int buflength,
                  const struct city *pcity);
void dai_unit_log(struct ai_type *ait, char *buffer, int buflength,
                  const struct unit *punit);

QString tech_log_prefix(ai_type *ait, const player *pplayer,
                        advance *padvance);
#define TECH_LOG(ait, _, pplayer, padvance, msg, ...)                       \
  {                                                                         \
    bool notify = BV_ISSET(pplayer->server.debug, PLAYER_DEBUG_TECH);       \
    QString message = tech_log_prefix(ait, pplayer, padvance)               \
                      + QStringLiteral(" ")                                 \
                      + QString::asprintf(msg, ##__VA_ARGS__);              \
    if (notify) {                                                           \
      qCInfo(ai_category).noquote() << message;                             \
      notify_conn(nullptr, nullptr, E_AI_DEBUG, ftc_log, "%s",              \
                  qUtf8Printable(message));                                 \
    } else {                                                                \
      qCDebug(ai_category).noquote() << message;                            \
    }                                                                       \
  }

QString diplo_log_prefix(ai_type *ait, const player *pplayer,
                         const player *aplayer);
#define DIPLO_LOG(ait, loglevel, pplayer, aplayer, msg, ...)                \
  {                                                                         \
    bool notify = BV_ISSET(pplayer->server.debug, PLAYER_DEBUG_DIPLOMACY);  \
    QString message = diplo_log_prefix(ait, pplayer, aplayer)               \
                      + QStringLiteral(" ")                                 \
                      + QString::asprintf(msg, ##__VA_ARGS__);              \
    if (notify) {                                                           \
      qCInfo(ai_category).noquote() << message;                             \
      notify_conn(nullptr, nullptr, E_AI_DEBUG, ftc_log, "%s",              \
                  qUtf8Printable(message));                                 \
    } else {                                                                \
      qCDebug(ai_category).noquote() << message;                            \
    }                                                                       \
  }

QString bodyguard_log_prefix(ai_type *ait, const unit *punit);
#define BODYGUARD_LOG(ait, loglevel, punit, msg, ...)                       \
  {                                                                         \
    bool notify = punit->server.debug;                                      \
    QString message = bodyguard_log_prefix(ait, punit)                      \
                      + QStringLiteral(" ")                                 \
                      + QString::asprintf(msg, ##__VA_ARGS__);              \
    if (notify) {                                                           \
      qCInfo(ai_category).noquote() << message;                             \
      notify_conn(nullptr, nullptr, E_AI_DEBUG, ftc_log, "%s",              \
                  qUtf8Printable(message));                                 \
    } else {                                                                \
      qCDebug(ai_category).noquote() << message;                            \
    }                                                                       \
  }
