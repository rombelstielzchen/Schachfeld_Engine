#!/usr/bin/bash

# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

BIN_DIR='../older_versions'

echo "### Packaing Release ###"
# Get path to "last" executable, alphabetically
BINARY=$(ls -d -1 $BIN_DIR/* | tail -1)
# Get the name without exe-extension, to be used as directory-namee
TARGET_DIR=$(ls -1 $BIN_DIR/* | tail -1 | xargs basename | sed -e "s/\.exe//;")

# Copying all needed files
rm -rf $TARGET_DIR
mkdir $TARGET_DIR
cp $BINARY $TARGET_DIR
cp ../README.md $TARGET_DIR
cp -R ../docs/ $TARGET_DIR
rm -rf $TARGET_DIR/docs/developers/

# Final Report
echo -n "Binary: "
ls -d $TARGET_DIR/* | grep exe
echo -n "Archive: "
ls -l -d *.ziip

