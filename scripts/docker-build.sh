#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors
# SPDX-FileCopyrightText: XHawk87 <hawk87@hotmail.co.uk>
set -e

cd "$(dirname "$0")/.."

docker build --tag freeciv21-builder:latest --file .docker/Dockerfile.builder .
docker run --rm \
  --volume "$(pwd -P):/usr/src/freeciv21" \
  freeciv21-builder:latest /usr/src/freeciv21/.docker/build.sh "$@"

