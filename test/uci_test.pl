#!/usr/bin/perl

# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby
#
# Requirements:
#   * a Linux-like command-line with bash, perl and tail
#   * the script poor_mans_tail.sh in this directory
#   * an executable "engine" in ../src
#
# This script does ATM not work  with Windows-executables, but propably will do
# if you redefine $engine_command below and use a shell like Git-Bash.

use strict;
use warnings; 

my $output_pipe;
my $intermediate_file = 'temp.txt';
my $result_file = 'temp2.txt';
my $engine_command = '../src/engine';
my $timeout_sec = 10;

### Functions ##########################

sub simple_tail {
    # A proper implementation of this test-script
    # should simply pipe commands to and results from the engine.
    # This fails, probably due to too much output and too small buffers.
    # So we take the ugöy route with temp-files.
    system("bash", "./poor_mans_tail.sh");
    open(my $fh, "<", $result_file)
        or die "open() failed $!";
    my $result = <$fh>;
    close ($fh);
    return $result;
}

sub EXPECT {
   my $expected_result = shift(@_);
   my $tail_result = "";
   for (my $j = 0; $j < $timeout_sec; ++$j) {
        sleep(1);
        $tail_result = simple_tail();
        chomp($tail_result);
        if ($tail_result eq $expected_result) {
            print "<< ", $tail_result, "\n";
            return;
        }
   }
    die "Unexpected result: $tail_result\n";
}

### BOMP ### Begin Of Main Program #####

# Start engine, control via outputi_pipe, redirect to intermediate_file
my $engine_PID = open($output_pipe, '|-', "$engine_command > $intermediate_file")
    or die "open() failed $!";
print "started engine. PID: ", $engine_PID, " \n";
#print "Going to test...\n"
#
print $output_pipe "uci\n";
#
print $output_pipe "isready\n";
sleep(40);

print simple_tail();
EXPECT("readyok");
#
print "All tests passed successfully\n";

### Clean-up ###########################
unlink $intermediate_file;
unlink $result_file;
exit;

