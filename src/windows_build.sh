#!/usr/bin/bash

# Simple script to build the Schachfeld-engine on windows for command-line-fetishists
#
# Prereqzisites:
#   * Windows
#   * a Linux-like shell like git-bash 
#   * Visual Studio

MiSoViStu="/c/Programme/Microsoft Visual Studio/2022/Community/Common7/IDE/devenv.exe"
EngineProject="visual_studio/Schachfeld_Engine.vcxproj"

echo "Going to build $EngineProject"
echo "iUsing $MiSoViStu"

"$MiSoViStu" "$EngineProject" -build -log x.txt

