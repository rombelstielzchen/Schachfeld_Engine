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
use warnings;

use constant ENGINE => "../src/engine";
use constant EXIT_SUCCESS => 0;
use constant EXIT_FAILURE => 1;
use constant MODE_INPUT_PIPE => "-|";
use constant MODE_OUTPUT_PIPE => "|-";

my $output_pipe;
my $input_pipe;

sub EXPECT {
    my ($condition) = @_;
    if (!$condition) {
        die "[ERROR] condition failed\n";
    }
}

sub send_message {
    my ($message) = @_;
    print ">>> ", $message;
    print $output_pipe $message;
}

sub start_engine {
    print "Starting engine: @{[ ENGINE ]}\n";
    my $pid = fork();
    die "Failed to foek: $!" unless defined $pid;
    if ($pid == 0) {
        exit;
        exec(ENGINE);
        # exec replaces the process and never returns.
        # No further script actions in this case
    }
    die "Unexpected PID after fork" if $pid == 0;
    our $child_pid = $pid;
    print "Child PID: $child_pid\n";
    print "Setting up pipes for communication ...\n";
    open $output_pipe, MODE_OUTPUT_PIPE, @{[ ENGINE ]} or die $!;
    open input_pipe, MODE_INPUT_PIPE, @{[ ENGINE ]} or die $!;
    send_message("uci\n");
    send_message("isready\n");
    send_message("quit\n");
}

#sub await_inout { 
#    my ($expected_input, $timeout_seconds) = @_;
#    my $input = "";
#    while ($input neq "readyok") {
#        $input = <>;
#    }
#    print "gugu";
    #}

### BOMP -- Begin Of Main Program ######
print "### Quick Engine Test ########\n";
start_engine();
exit(EXIT_SUCCESS);

