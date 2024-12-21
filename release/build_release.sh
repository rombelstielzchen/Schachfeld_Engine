#!/usr/bin/bash

# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

# Preconditions:
#   * Linux-engine built and tested, simply "make"
#   * Windows engine built with MiSo ViStu in Release-mode
#   * Windows-executable renamed with version-number, e.g. Schachfeld_Engine_3.1
#   * Execztable moved to binaries-directory. see below ...

BIN_DIR='../older_versions'

echo "### Packaing Release ###"
# Get path to "last" executable, alphabetically
BINARY=$(ls -d -1 $BIN_DIR/* | tail -1)
# Get the name without exe-extension, to be used as directory-namee
TARGET_DIR=$(ls -1 $BIN_DIR/* | tail -1 | xargs basename | sed -e "s/\.exe//;")
ZIP_FILE=$(echo $TARGET_DIR | sed -e "s/$/.zip/;")

# Copying all needed files
rm -rf $TARGET_DIR
mkdir $TARGET_DIR
cp $BINARY $TARGET_DIR
cp ../README.md $TARGET_DIR
cp -R ../docs/ $TARGET_DIR
rm -rf $TARGET_DIR/docs/developers/

# Buil a zip-archive
zip -r $ZIP_FILE $TARGET_DIR

# Final Report
echo -n "Binary: "
ls -d $TARGET_DIR/* | grep exe
echo -n "Archive: "
ls -l -d $ZIP_FILE
unzip -l $ZIP_FILE

