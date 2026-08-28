#!/bin/bash
# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors
# SPDX-FileCopyrightText: XHawk87 <hawk87@hotmail.co.uk>
set -e
cd /usr/src/freeciv21
changed_files=()
while IFS= read -r file_path; do
  case "$file_path" in
    *.h|*.hpp|*.hh|*.hxx|*.c|*.cc|*.cpp|*.cxx)
      changed_files+=("$file_path")
      ;;
  esac
done < <(
  git diff --name-only --diff-filter=ACMRTUXB
  git ls-files --others --exclude-standard
  git diff --name-only --cached
)
if (( ${#changed_files[@]} > 0 )); then
  clang-tidy "${changed_files[@]}" -p build-clang/ "$@"
else
  echo "No uncommitted changes to tidy" >&2
fi

