#!/usr/bin/bash

g++ -c DebugLog.cpp
g++ -D DEBUG_LOG_ENABLE Program.cpp DebugLog.o
