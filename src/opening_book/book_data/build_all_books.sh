#!/bin/bash

# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

# Requirements: a Linux-like command-line.
# On Windows consider WSL or git-bash.
#
# Usage: ./build_all_books.sh
#   (no arguments)

# Safer bashing
set -o errexit
set -o nounset

BUILD='./build_book.sh'

$BUILD gm_book 10 10
$BUILD tabijas  5 30
$BUILD wonder_weapons_black 3 30
$BUILD wonder_weapons_white 3 30

