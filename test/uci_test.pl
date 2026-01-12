#!/usr/bin/perl

# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby
#
# Requirements:
#   * a Linux-like command-line with bash, cat, grep, perl, tail
#   * a Linux-executable "engine" in ../src
#     or a Windows-executable in "../older_versions"

use strict;
use warnings; 
use File::Basename;

print "### UCI-Test ###\n";

my $n_repetitions = 1;
if ((scalar(@ARGV) == 1) && ($ARGV[0] eq "--stress")) {
    print "Stress-test chosen\n";
    $n_repetitions = 1234;
}
print "Repetitions: $n_repetitions:\n";

my $engine_command = '../src/engine';
my $os_version = `cat /proc/version`;
print "OS version: $os_version"; 
my $is_windows = ($os_version ~~ m/MINGW/);
if ($is_windows) {
    print "Operating-system: Windows\n";
    print "Choosing latest executable from 'older_versions'\n";
    $engine_command = `ls -d -1 ../older_versions/* | grep -i exe | tail -1`;
} else {
    print "Operating-system: Linux\n";
    print "Choosing default engine\n";
}
print "Chess-engine: $engine_command\n";

my $output_pipe;
my $intermediate_file = 'temp.txt';
my $result_file = 'temp2.txt';
my $pgn_file = "schachfeld_games.pgn";
my $startup_safety_delay_sec = 60;
my $timeout_sec = 30;

### Functions ##########################

sub send_message {
    my $message = shift(@_);
    chomp($message);
    print ">> $message\n";
    print $output_pipe "$message\n";
}

sub simple_tail {
    # A proper implementation of this test-script
    # should simply pipe commands to and results from the engine.
    # This fails, probably due to too much output and too small buffers.
    # So we take the ugly route with temp-files.
    if (!-e $intermediate_file) {
        return "$intermediate_file does not (yet) exist";
    }
    `tail -n 1 < $intermediate_file > $result_file`;
    open(my $fh, "<", $result_file)
        or return ""; 
    my $result = <$fh>;
    close ($fh);
    if (!defined $result) {
        return "";
    }
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
            print "<< $tail_result\n";
            return;
        }
   }
    print "Unexpected result: $tail_result\n";
    send_message("quit");
     "UCI-Test failed\n";
}

sub start_engine {
    # Start engine, control via output_pipe, redirect to intermediate_file
    my $engine_PID = open($output_pipe, '|-', "$engine_command > $intermediate_file")
        or  "open() failed $!";
    print "started engine. PID: $engine_PID\n";
    for (my $j = $startup_safety_delay_sec; $j > 0; --$j) {
        print "Ready for operations in $j seconds\n";
        sleep(1);
    }
}

### BOMP ### Begin Of Main Program #####
start_engine();
for (my $j = 0; $j < $n_repetitions; ++$j) {
    # Testing UCI startup
    send_message("uci");
    EXPECT("uciok");
    send_message("isready");
    EXPECT("readyok");
    # Testing opening book
    send_message("position startpos moves e2e4 e7e5 d2d4");
    send_message("go depth 123456789");
    EXPECT("bestmove e5d4");
    # Testing go-commands
    send_message("position startpos moves f2f3 e7e5 g2g4");
    send_message("go depth 2");
    EXPECT("bestmove d8h4");
    send_message("go mate 1");
    EXPECT("bestmove d8h4");
    send_message("go nodes 1000");
    EXPECT("bestmove d8h4");
    send_message("go movetime 1000");
    EXPECT("bestmove d8h4");
    send_message("go time btime 2000 binc 2000 movestogo 39");
    EXPECT("bestmove d8h4");
    send_message("go infinite");
    sleep(3);
    send_message("stop");
    EXPECT("bestmove d8h4");
    # Testing FEN position
    send_message("position fen K1k w");
    send_message("go depth 3");
    EXPECT("bestmove a8a7");
    # Testing immediate response on only move
    send_message("go depth 123456789");
    EXPECT("bestmove a8a7");
    # Testing console extension
    send_message("help");
    EXPECT("    * 'quit' or 'x'to terminate");
    send_message('psv');
    EXPECT('avg: -20000');
    send_message("p s m e2e4");
    send_message("d7d5");
    send_message("f1c4");
    send_message("g d 2");
    EXPECT("bestmove d5c4");
    send_message("back");
    send_message("d2d4");
    send_message("g");
    sleep(2);
    send_message("s");
    EXPECT("bestmove d5e4");
}
# Done!
send_message("quit");
print "All tests passed successfully\n";

### Clean-up ###########################
unlink $intermediate_file;
unlink $result_file;
unlink $pgn_file;
exit;

