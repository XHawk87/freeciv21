/*
 Copyright (c) 1996-2020 Freeciv21 and Freeciv contributors. This file is
 part of Freeciv21. Freeciv21 is free software: you can redistribute it
 and/or modify it under the terms of the GNU  General Public License  as
 published by the Free Software Foundation, either version 3 of the
 License,  or (at your option) any later version. You should have received
 a copy of the GNU General Public License along with Freeciv21. If not,
 see https://www.gnu.org/licenses/.
 */

// common
#include "featured_text.h"
#include "game.h"

/* common/scriptcore */
#include "luascript.h"

// client
#include "chatline_common.h"
#include "client_main.h"

#include "api_client_base.h"

/**
   Print a message in the chat window.
 */
void api_client_chat_base(lua_State *L, const char *msg)
{
  LUASCRIPT_CHECK_STATE(L);
  LUASCRIPT_CHECK_ARG_NIL(L, msg, 2, string);

  output_window_printf(ftc_chat_luaconsole, "%s", msg);
}

/**
 * Return the number of seconds since the last turn change.
 */
double api_client_game_seconds_since_turn_change(lua_State *L)
{
  LUASCRIPT_CHECK_STATE(L, 0);
  LUASCRIPT_CHECK(L, current_turn_timeout() > 0,
                  "The timeout is currently disabled.", 0);
  LUASCRIPT_CHECK(L, get_seconds_to_turndone() != FC_INFINITY,
                  "The game is currently not running.", 0);
  return current_turn_timeout() - get_seconds_to_turndone();
}

/**
 * Return the number of seconds until the next turn change.
 */
double api_client_game_seconds_to_turn_change(lua_State *L)
{
  LUASCRIPT_CHECK_STATE(L, 0);
  LUASCRIPT_CHECK(L, current_turn_timeout() > 0,
                  "The timeout is currently disabled.", 0);
  LUASCRIPT_CHECK(L, get_seconds_to_turndone() != FC_INFINITY,
                  "The game is currently not running.", 0);
  return get_seconds_to_turndone();
}
