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
#
# ATTENTION!
#
# Connecting the engine via pipe to the intermediate_file seems to be broken on Windows,
# Therefore validation of the result temp disabled on Windows.

use strict;
use warnings; 
use File::Basename;
use Time::HiRes 'usleep';

### Constants and global variables #####

use constant true => 1;
use constant false => 0;

my $intermediate_file = 'temp.txt';
my $result_file = 'temp2.txt';
my $pgn_file = "schachfeld_games.pgn";

my $engine_PID = -1;
my $output_pipe;
my $startup_safety_delay_sec = 220;
my$ selftest_chosen = false;

STDOUT->autoflush(1);
print "### UCI-Test ###\n";

### Configuration ######################

my $n_repetitions = 1;
if ((scalar(@ARGV) == 1) && ($ARGV[0] eq "--stress")) {
    print "Stress-test chosen\n";
    $selftest_chosen = true;
    $n_repetitions = 1234;
} elsif ((scalar(@ARGV) == 1) && ($ARGV[0] eq "--selftest")) {
    print "Selftest only\n";
    $selftest_chosen = true;
    $n_repetitions = 0;
} elsif ((scalar(@ARGV) == 1) && ($ARGV[0] eq "--quit")) {
    print "Early exit chosen\n";
    $n_repetitions = 0;
} elsif (scalar(@ARGV) > 0) {
    die "ERROR: Unknown argument(s): @ARGV";
}
print "Repetitions: $n_repetitions:\n";
print "Selftest chosen: $selftest_chosen\n";

my $engine_command = '../src/engine';
my $os_version = `cat /proc/version`;
print "OS version: $os_version"; 
my $is_windows = ($os_version ~~ m/MINGW/);
if ($is_windows) {
    print "Operating-system: Windows\n";
    print "Choosing latest executable from 'older_versions'\n";
    $engine_command = `ls -t -1 ../older_versions/* | grep -i exe | head -1`;
} else {
    print "Operating-system: Linux\n";
    print "Choosing default engine\n";
}
print "Chess-engine: $engine_command\n";
my $test_timeout_sec = 300;

### BOMP ### Begin Of Main Program #####
`touch $intermediate_file`;
start_engine();
if ($selftest_chosen) {
    send_message('test');
}
for (my $j = 1; $j <= $n_repetitions; ++$j) {
       print "Starting iteration $j of $n_repetitions\n";
       test_all();
}
close_engine();
print "All tests passed successfully\n";
exit;

### General Functions ##################

sub send_message {
    my $message = shift(@_);
    chomp($message);
    print ">> $message\n";
    print $output_pipe "$message\n";
    $output_pipe->flush();
}

sub intermediate_contains {
    # We must check the entire file, not just the end,
    # otherwise the asynchronous statistics-thread can mess things up
    my $wanted = shift(@_);
    open my $fh, '<', $intermediate_file or die $!;
    system("tail -n 7 $intermediate_file > $result_file");
    my $found = system("grep -qF " . quotemeta($wanted) . " $intermediate_file") == 0;
    close $fh;
    return $found;
}

sub EXPECT {
    if ($is_windows) {
        sleep(1);
        send_message("stop");
        sleep(1);
        return;
    }
    my $expected_result = shift(@_);
    my $start_time = time;
    while (time() <= ($start_time + $test_timeout_sec)) {
        usleep(0.2);
        if (intermediate_contains($expected_result)) {
            print "<< $expected_result\n";
            return;
        }
   }
    print "Failed to find '$expected_result'\n";
    system("tail -n 5 $intermediate_file");
    system('cp temp.txt fail.txt');
    send_message('quit');
   die  "UCI-Test failed\n";
}

sub start_engine {
    # Start engine, control via output_pipe, redirect to intermediate_file
    $engine_PID = open($output_pipe, '|-', "$engine_command > $intermediate_file")
        or die "open() failed $!";
#`echo xxx > $intermediate_file`;
    print "started engine. PID: $engine_PID\n";
    await_ready_engine();
}

sub await_ready_engine {
    # Nowadays the selftest is blocking again and no longer starting automatically.
    # So all we have to do: query readiness
    send_message('isready');
    EXPECT('readyok');
}

sub close_engine {
    # Nearly done! "Testing" quit-command
    print "Going to quit (soon)\n!";
    print "But first starting a new position, still expecting a result\n";
    send_message('position fen k1KQq w');
    EXPECT('info new position: k1KQq3/8/8/8/8/8/8/8 w - - 0 1');
    sleep(1);
    send_message('g');
    sleep(3);
    send_message('quit');
    EXPECT('bestmove d8e8');
}

END {
    print "Auto-cleanup...";
    #    unlink $intermediate_file;
    unlink $result_file;
    unlink $pgn_file;
    if ($engine_PID > 0) {
        kill 9, $engine_PID;
    }
    print "Done\n";
}

### Test-Cases #########################

sub test_01 {
    # Testing UCI startup
    send_message('uci');
    EXPECT('uciok');
 }

sub test_02 {
    # Testing isready
    send_message('isready');
    EXPECT('readyok');
}

sub test_03 {
    # Testing opening book
    send_message('position startpos moves e2e4 e7e5 d2d4');
    send_message('go depth 123456789');
    EXPECT('bestmove e5d4');
}

sub test_03a {
    # Testing (repeated) setposition
    send_message('position startpos moves e2e4 e7e5 d2d4');
    send_message('position fen k1K w');
    send_message('position fen k1K//R b');
}

sub test_04 {
    # Testing go-command (depth)
    send_message('position startpos moves e2e4 e7e5 f1a6');
    send_message('go depth 2');
    EXPECT('bestmove b8a6');
}

sub xxxx {
    #
    send_message('position startpos moves e2e4 g8f6 d1h5');
     send_message('go depth 2');
    EXPECT('bestmove f6h5');
    #
    send_message('position startpos moves f2f3 e7e5 g2g4');
    send_message('go depth 2');
    EXPECT('bestmove d8h4');
}

sub test_05 {
    # Testing go-command (mate)
    send_message('position startpos moves f2f3 e7e5 g2g4');
    send_message('go mate 1');
    EXPECT('bestmove d8h4');
}

sub test_06 {
    # Testing go-command (nodes)
    send_message('position startpos moves f2f3 e7e5 g2g4');
    send_message('go nodes 1000');
    EXPECT('bestmove d8h4');
}

sub test_07 {
    # Testing go-command (movetime)
    send_message('position startpos moves f2f3 e7e5 g2g4');
    send_message('go movetime 1000');
    EXPECT('bestmove d8h4');
}

sub test_08 {
    # Testing go-command (time)
    send_message('position startpos moves f2f3 e7e5 g2g4');
    send_message('go time btime 2000 binc 2000 movestogo 39');
    EXPECT('bestmove d8h4');
}

sub test_09 {
    # Testing go-command (infinite)
    # Then once more, with isready inbetween
    send_message('position startpos moves f2f3 e7e5 g2g4');
    send_message('go infinite');
    sleep(3);
    send_message('stop');
    EXPECT('bestmove d8h4');
    #
    send_message('go infinite');
    sleep(2);
    send_message('isready');
    EXPECT('readyok');
    send_message('stop');
    EXPECT('bestmove d8h4');
}

sub test_10 {
    # Testing FEN position
    send_message('position fen K1k w');
    send_message('go depth 3');
    EXPECT('bestmove a8a7');
}

sub test_11 {
    # Testing immediate response on only move
    send_message('position fen K1k w');
    send_message('go depth 123456789');
    EXPECT('bestmove a8a7');
}

sub test_12 {
    # Testing console extension (help)
    send_message('help');
    EXPECT("    * 'quit' or 'x'to terminate");
}

sub test_13 {
    # Testing console extension (psv)
    send_message('psv');
    EXPECT('avg: -20000');
}

sub test_14 {
    # Testing console extension (abbreviated commands)
    send_message('p s m e2e4');
    send_message('d7d5');
    send_message('f1c4');
    send_message('g d 2');
    EXPECT('bestmove d5c4');
}

sub test_15 {
    # Testing console extension (back)
    send_message('p s m e2e4');
    send_message('d7d5');
    send_message('f1c4');
    send_message('back');
    send_message('d2d4');
    send_message('g');
    sleep(2);
    send_message('s');
    EXPECT('bestmove d5e4');
}

sub test_all {
    test_01();
    test_02();
    test_03();
    test_03a();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
    test_09();
    test_10();
    test_11();
    test_12();
    test_13();
    test_14();
    test_15();
}

