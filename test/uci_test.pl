#!/usr/bin/perl

# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby
#
# Requirements:
#   * a Linux-like command-line with bash, perl and tail
#   * an executable "engine" in ../src
#
# This script does ATM not work  with Windows-executables, but propably will do
# if you redefine $engine_command below and use a shell like Git-Bash.

use strict;
use warnings; 
use File::Basename;

my $n_repetitions = 1;
if ((scalar(@ARGV) == 1) && ($ARGV[0] == "--stress")) {
    $n_repetitions = 789
}

my $output_pipe;
my $intermediate_file = 'temp.txt';
my $result_file = 'temp2.txt';
my $pgn_file = "schachfeld_games.pgn";
my $engine_command = '../src/engine';
my $startup_safety_delay_sec = 60;
my $timeout_sec = 10;

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
        `tail -n 1 < $intermediate_file > $result_file`;
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
            print "<< $tail_result\n";
            return;
        }
   }
    print "Unexpected result: $tail_result\n";
    send_message("quit");
   die  "UCI-Test failed\n";
}

sub start_engine {
    # Start engine, control via output_pipe, redirect to intermediate_file
    my $engine_PID = open($output_pipe, '|-', "$engine_command > $intermediate_file")
        or die "open() failed $!";
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

