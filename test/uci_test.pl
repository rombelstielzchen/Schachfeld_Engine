#!/usr/bin/perl

use strict;
use warnings; 

my $output_pipe;
my $intermediate_file = 'temp.txt';
my $result_file = 'temp2.txt';
my $engine_command = '../src/engine';
my $timeout_sec => 10;

### Functions ##########################

sub simple_tail {
    system("bash", "./poor_mans_tail.sh");
    open(my $fh, "<", $result_file)
        or die "open() failed $!";
    my $result = <$fh>;
    close ($fh);
    return $result;
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

system("bash", "./poor_mans_tail.sh");
sleep(1);
print "---\n";
open(my $fh, "<", $result_file) or die '$1+!';
print <$fh>, "\n";
print simple_tail(), "\n";
exit;

#my $tail_PID = open($input_pipe, '-|', "tail -n 1  < $intermediate_file")
#    or die "open() failed $!";
#print "started tail. PID:: ", $tail_PID, "\n";
#
#sleep(3);
#while (my $x = <$input_pipe>) {
#print $x;
#}


#print "Going to send message: 12345\n";
#print $output_pipe "12345\n";
#print "Alive after sending\n";
#my $result = <$input_pipe>;
#print "Alive after reading result\n";
#print "Result: ", $result, "\n";
