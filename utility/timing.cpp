// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

// self
#include "timing.h"

// utility
#include "log.h"

// Qt
#include <QDateTime>
#include <QElapsedTimer>
#include <QLoggingCategory>
#include <QTimeZone>
#include <QtLogging> // qDebug, qWarning, qCritical, etc

Q_LOGGING_CATEGORY(timers_category, "freeciv.timers")

enum timer_state { TIMER_STARTED, TIMER_STOPPED };

class civtimer : public QElapsedTimer {
public:
  civtimer(enum timer_timetype type, enum timer_use use);
  enum timer_state state;
  enum timer_timetype type;
  enum timer_use use;
  double sec;
  int msec;
};

civtimer::civtimer(enum timer_timetype ttype, enum timer_use tuse)
    : QElapsedTimer(), state(TIMER_STOPPED), type(ttype), use(tuse),
      sec(0.0), msec(0)
{
}

/**
   Allocate a new timer with specified "type" and "use".
 */
civtimer *timer_new(enum timer_timetype type, enum timer_use use)
{
  return timer_renew(nullptr, type, use);
}

/**
   Allocate a new timer, or reuse t, with specified "type" and "use".
 */
civtimer *timer_renew(civtimer *t, enum timer_timetype type,
                      enum timer_use use)
{
  if (!t) {
    t = new civtimer(type, use);
  }
  t->type = type;
  t->use = use;
  timer_clear(t);
  return t;
}

/**
   Deletes timer
 */
void timer_destroy(civtimer *t)
{
  delete t;
  t = nullptr;
}

/**
   Return whether timer is in use.
   t may be nullptr, in which case returns 0
 */
bool timer_in_use(civtimer *t) { return (t && t->use != TIMER_IGNORE); }

/**
   Reset accumulated time to zero, and stop timer if going.
   That is, this may be called whether t is started or stopped;
   in either case the timer is in the stopped state after this function.
 */
void timer_clear(civtimer *t)
{
  fc_assert_ret(nullptr != t);
  t->state = TIMER_STOPPED;
  t->sec = 0.0;
  t->msec = 0;
}

/**
   Start timing, adding to previous accumulated time if timer has not
   been cleared.  A warning is printed if the timer is already started.
 */
void timer_start(civtimer *t)
{
  fc_assert_ret(nullptr != t);

  if (t->use == TIMER_IGNORE) {
    return;
  }
  if (t->state == TIMER_STARTED) {
    qCritical("tried to start already started timer");
    return;
  }
  t->state = TIMER_STARTED;
  t->restart();
}

/**
   Stop timing, and accumulate time so far.
   (The current time is stored in t->start, so that timer_read_seconds
   can call this to take a point reading if the timer is active.)
   A warning is printed if the timer is already stopped.
 */
void timer_stop(civtimer *t)
{
  fc_assert_ret(nullptr != t);

  if (t->use == TIMER_IGNORE) {
    return;
  }
  if (t->state == TIMER_STOPPED) {
    qCritical("tried to stop already stopped timer");
    return;
  }
  t->msec = t->elapsed();
  t->sec = (double(t->elapsed()) / 1000);
  t->state = TIMER_STOPPED;
}

/**
   Read value from timer.  If the timer is not stopped, this stops the
   timer, reads it (and accumulates), and then restarts it.
   Returns 0.0 for unused timers.
 */
double timer_read_seconds(civtimer *t)
{
  fc_assert_ret_val(nullptr != t, -1.0);

  if (t->use == TIMER_IGNORE) {
    return 0.0;
  }
  if (t->state == TIMER_STARTED) {
    timer_stop(t);
    t->state = TIMER_STARTED;
  }
  return t->sec;
}

/**
 * Return a unix timestamp in fractional seconds since the epoch to
 * millisecond precision.
 */
double seconds_since_epoch()
{
  return QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()
         / MILLISECONDS_IN_A_SECOND;
}

/**
 * Convert a unix timestamp in seconds since the epoch to an ISO-8601
 * date-time string. E.g. 2026-08-08T10:44:37Z
 */
const char *to_iso8601_datetime(qint64 unix_timestamp)
{
  return QDateTime::fromSecsSinceEpoch(unix_timestamp, QTimeZone::UTC)
      .toString(Qt::ISODate)
      .toUtf8()
      .constData();
}

/**
 * Convert a duration in seconds to an ISO-8601 duration string. E.g. P3DT4H
 */
const char *to_iso8601_duration(qint64 seconds)
{
  // Seriously Qt, why no QTimeSpan?
  thread_local QByteArray s;
  const bool neg = seconds < 0;
  quint64 sec = neg ? quint64(-(seconds + 1)) + 1 : quint64(seconds);

  qint64 days = sec / DAY_IN_SECONDS;
  sec %= DAY_IN_SECONDS;
  qint64 hours = sec / HOUR_IN_SECONDS;
  sec %= HOUR_IN_SECONDS;
  qint64 mins = sec / MINUTE_IN_SECONDS;
  sec %= MINUTE_IN_SECONDS;

  s.clear();
  if (neg) {
    s += '-';
  }
  s += 'P';
  if (days) {
    s += QByteArray::number(days) + 'D';
  }

  if (hours || mins || sec || !days) {
    s += 'T';
    if (hours) {
      s += QByteArray::number(hours) + 'H';
    }
    if (mins) {
      s += QByteArray::number(mins) + 'M';
    }
    if (sec || (!hours && !mins)) {
      s += QByteArray::number(sec) + 'S';
    }
  }

  return s.constData();
}
