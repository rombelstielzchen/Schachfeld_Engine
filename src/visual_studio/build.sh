#!/usr/bin/bash 

# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

# This script requires:
#   * Windows
#   * a Linux-like command-line, e.g. Git-Bash
#   * Visual Studio
#
# If you want to forcce a rebuild "make clean" in the parent directpry first
# or "make exe".

# http://web.archive.org/web/20110314180918/http://www.davidpashley.com/articles/writing-robust-shell-scripts.html
set -o errexit
set -o nounset

# Configure your path toe devenv here
DEVENV='/c/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/devenv.com'

PARTS='vcxproj_parts/'
VCX_START="${PARTS}vcxproj.start.xml"
VCX_END="${PARTS}vcxproj.end.xml"
VCXPROJ="Schachfeld_Engine.vcxproj"
TMP_CPP='cpp.tmp'
TMP_H='h.tmp'

echo 'Going to create MiSo ViStu files...'
# Collecting data
find .. -iname *.cpp | sed '/\/docu_/d' | sed 's/^/<clCompile Include=\"/' | sed 's/$/\"\/>/' > "${TMP_CPP}"
find .. -iname *.h | sed '/\/docu_/d' | sed 's/^/<clInclude Include=\"/' | sed 's/$/\"\/>/'  > "${TMP_H}"
# VCXPROJ
cp "${VCX_START}" "${VCXPROJ}"
cat "${TMP_CPP}" >> "${VCXPROJ}"
echo "  </ItemGroup>" >> "${VCXPROJ}"
echo "  <ItemGroup>" >> "${VCXPROJ}"
cat "${TMP_H}" >> "${VCXPROJ}"
cat "${VCX_END}" >> "${VCXPROJ}"
# No vcxproj.filters needed
# Clean up
rm -f "${TMP_CPP}"
rm -f "${TMP_H}"
wc *.vcxproj

echo 'Going to build project ...'
# hhttps://learn.microsoft.com/en-us/visualstudio/ide/reference/devenv-command-line-switches?view=vs-2022ttps://learn.microsoft.com/en-us/visualstudio/ide/reference/devenv-command-line-switches?view=vs-2022
"${DEVENV}" "${VCXPROJ}" -build
ls -o x64/Release/*.exe

# Copying executable to new destination
EXE="./x64/Release/Schachfeld_Engine.exe"
ENGINE_VERSION=$(printf "uci\nquit\n" | ("$EXE" 2> /dev/null) | grep "id name" | sed "{ s/id name //; }")
echo "Found engine version: $ENGINE_VERSION"
NEW_NAME="${ENGINE_VERSION}.exe"
NEW_PATH="../../older_versions/${NEW_NAME}"
echo "Copying from $EXE"
ls -o $EXE
echo "Copying to $NEW_PATH"
cp -f "$EXE" "$NEW_PATH"
ls -o "$NEW_PATH"

