#!/usr/bin/env bash
# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors
# SPDX-FileCopyrightText: XHawk87 <hawk87@hotmail.co.uk>
set -e
cd /usr/src/freeciv21
cmd="${1:-build}"
shift
case "$cmd" in
  tidy)
    cmake --preset clang
    [[ -d build-clang ]] || cmake --build build-clang
    case "${1:-}" in
      '')
        ./.docker/clang-tidy-uncommitted-changes.sh \
            --checks="-*,misc-include-cleaner"
      ;;
      uncommitted) shift; ./.docker/clang-tidy-uncommitted-changes.sh "$@" ;;
      *) clang-tidy -p build-clang "$@" ;;
    esac
  ;;
  'test')
    cmake . --preset clang
    cmake --build build-clang
    cmake --build build-clang --target test
    ./.docker/clang-tidy-uncommitted-changes.sh \
        --checks="-*,misc-include-cleaner" --warnings-as-errors="*"
  ;;
  build)
    build_dir="${CMAKE_BUILD_PREFIX:-build-docker}"
    build_opts=(
        -DFREECIV_ENABLE_TOOLS="${FREECIV_ENABLE_TOOLS:-ON}"
        -DFREECIV_ENABLE_SERVER="${FREECIV_ENABLE_SERVER:-ON}"
        -DFREECIV_ENABLE_NLS="${FREECIV_ENABLE_NLS:-ON}"
        -DFREECIV_ENABLE_CIVMANUAL="${FREECIV_ENABLE_CIVMANUAL:-ON}"
        -DFREECIV_ENABLE_CLIENT="${FREECIV_ENABLE_CLIENT:-ON}"
        -DFREECIV_ENABLE_FCMP_CLI="${FREECIV_ENABLE_FCMP_CLI:-ON}"
        -DFREECIV_ENABLE_FCMP_QT="${FREECIV_ENABLE_FCMP_QT:-ON}"
        -DFREECIV_ENABLE_RULEDIT="${FREECIV_ENABLE_RULEDIT:-ON}"
        -DFREECIV_ENABLE_RULEUP="${FREECIV_ENABLE_RULEUP:-ON}"
        -DFREECIV_ENABLE_MANPAGES="${FREECIV_ENABLE_MANPAGES:-ON}"
        -DFREECIV_USE_VCPKG="${FREECIV_USE_VCPGK:-OFF}"
        -DFREECIV_DOWNLOAD_FONTS="${FREECIV_DOWNLOAD_FONTS:-ON}"
        -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE:-Debug}"
        -DCMAKE_C_FLAGS_DEBUG="${CMAKE_C_FLAGS_DEBUG:--Og -ggdb}"
        -DCMAKE_CXX_FLAGS_DEBUG="${CMAKE_CXX_FLAGS_DEBUG:--Og -ggdb}"
        -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX:-$build_dir/install}"
    )
    cmake . -B "$build_dir" -G Ninja "${build_opts[@]}"
    cmake --build "$build_dir"
    cmake --build "$build_dir" --target install
  ;;
  *)
    echo "Unknown build parameter $1" >&2
    exit 1
  ;;
esac

