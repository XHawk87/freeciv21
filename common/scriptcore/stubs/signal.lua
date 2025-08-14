---@meta

-- Copyright (c) 1996-2020 Freeciv21 and Freeciv contributors. This file is
-- part of Freeciv21. Freeciv21 is free software: you can redistribute it
-- and/or modify it under the terms of the GNU  General Public License  as
-- published by the Free Software Foundation, either version 3 of the
-- License,  or (at your option) any later version. You should have received
-- a copy of the GNU General Public License along with Freeciv21. If not,
-- see https://www.gnu.org/licenses/.

-- SPDX-License-Identifier: GPL-3.0-or-later
-- SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors
-- SPDX-FileCopyrightText: XHawk87 <hawk87@hotmail.co.uk>

--  WARNING: do not attempt to change the name of the API functions.
--  They may be in use in Lua scripts in savefiles, so once released, the
--  name and signature cannot change shape even in new major versions of
--  Freeciv, until the relevant save format version can no longer be loaded.
--  If you really like to change a function name, be sure to keep also the
--  old one running.

-- Usage references:
-- https://longturn.readthedocs.io/en/latest/Contributing/style-guide.html
-- https://luals.github.io/wiki/definition-files
-- https://luals.github.io/wiki/annotations/#documenting-types
-- https://taminomara.github.io/sphinx-lua-ls/index.html#autodoc-directives
-- https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html#rst-primer

--- Signals are emitted by the server when certain events occur. (see
--- #Events for a list of specific signals). 
---
--- Signal emission invokes all associated callbacks in the order they were
--- connected. A callback can stop the current signal emission, preventing
--- callbacks connected after it from being invoked, by returning true.
---
--- !doctype table
--- @class signal
signal = {}


--- Register this Lua function to receive the given signal.
---
--- @param signal_name The #Event signal name to receive callbacks for
--- @param callback_name The global Lua function to call when this signal is
---                      emitted
function signal.connect(signal_name, callback_name)
end


--- Remove an existing registration of this Lua function to receive the given
--- signal.
---
--- @param signal_name The #Event signal name it should no longer receive
--                     callbacks for
--- @param callback_name The global Lua function that should no longer receive
---                      this signal callback
function signal.remove(signal_name, callback_name)
end


--- Check for an existing registration of this Lua function to receive the
--- given signal.
---
--- @param signal_name The #Event signal name to check if it receives callbacks
---                    for
--- @param callback_name The global Lua function to check if it receives this
---                      signal callback
--- @return boolean
function signal.defined(signal_name, callback_name)
    return true
end

--- List all signals as well as any callbacks, via log.normal(). Intended for
--- debugging.
function signal.list()
  local signal_id = 0;
  local signal_name = nil;

  log.normal("List of signals:");
  repeat
    local signal_name = find.signal(signal_id);
    if (signal_name) then
      local callback_id = 0;
      local callback_name = nil;

      log.normal("- callbacks for signal '%s':", signal_name);
      repeat
        local callback_name = find.signal_callback(signal_name, callback_id);
        if (callback_name) then
          log.normal("   [%3d] '%s'", callback_id, callback_name);
        end
        callback_id = callback_id + 1;
      until (callback_name == nil);

      signal_id = signal_id + 1;
    end
  until (signal_name == nil);
end


--- Refreshes an existing registration of this Lua function to receive the
--- given signal. This is intended for debugging purposes, and can be used for
--- modifying a callback handler function while the server is running.
---
--- @param signal_name The #Event signal name to receive callbacks for
--- @param callback_name The global Lua function to call when this signal is
---                      emitted
function signal.replace(signal_name, callback_name)
  if signal.defined(signal_name, callback_name) then
    signal.remove(signal_name, callback_name)
  end
  signal.connect(signal_name, callback_name)
end

--- Functions in this module are used to acquire objects for further
--- manipulation, given various kinds of identifying information. Functions are
--- overloaded so that a given object can be identified in several ways.
---
--- !doctype table
--- @class find
find = {}


--- Can be used to iterate over all defined signals (until nil is returned).
---
--- @return string The #Event signal name
function find.signal(index)
    return "signal_name"
end

--- Can be used to iterate over all callbacks currently associated with a given
--- signal. 
---
--- @return string The name of the global Lua function that receives the
---                callback for this signal
function find.signal_callback(signal_name, index)
    return "callback_name"
end

