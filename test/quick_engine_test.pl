#!/usr/bin/perl

# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

# Requirements:
#   * a Linux-like command-line
#   * an executable "engine" in ../src
# This script does ATM not work  with Windows-executables,
# but propably will do if you redefine ENGINE below and use a shell like Git-Bash.

use strict;
#use warnings;
use IPC::Open2;

use constant ENGINE => "../src/engine";
use constant EXIT_SUCCESS => 0;
use constant EXIT_FAILURE => 1;

my $input_pipe;
my $output_pipe;

print "Going to start engin: ", ENGINE, "\n";
my $pid = open2($input_pipe, $output_pipe, ENGINE)
    or die "open2() failed $!";
print "PID: ", $pid, "\n";

sleep 25;
print $output_pipe "isready\n";
#flush $output_pipe;
print "dadasd";
my $date = <input_pipe>;
print $pid, " huhu\n";
print "--- ", $date, " huhuhu\n";
#exit EXIT_SUCCESS;



