#!/usr/bin/perl

use Win32::SerialPort;
use Time::HiRes;


$COM = Win32::SerialPort->new("COM1");
$COM->baudrate(9600);
$COM->parity("N");
$COM->databits("8");
$COM->stopbits("1");
$COM->handshake("none");

&prepare();

$start = int($ARGV[0]);

open LOG, ">format.log";
close LOG;

for($c = $start; $c < 615; $c++)
{
	for($h = 0; $h < 4; $h++)
	{
		$s = 17 * ($h + 4 * $c);
		$r = &format($s);
		print STDERR "Formatting cylinder $c, head $h, status = $r\n";
		open LOG, ">>format.log";
		print LOG "Formatting cylinder $c, head $h, status = $r\n";
		close LOG;
	}
}

exit;


sub format()
{
	my $i = shift;
	my $ret;
	
	$time = time();
	
	# Start debugger
	&out("d");
	
	# Lay &out(disk format command
	&out("e 08|0000");
	&out("0600");
	&out(sprintf("%04X", $i));
	&out("1100");
	&out("0804");
	&out("0100");
	&out("0000");
	&out("FF00");
	&out("0000");
	&out("x");

	# Set PC to disk access routine
	&out("R pc 0000111E");
	
	# Call the routine
	&out("c");
	&out("c");
	
	sleep(1);

	# Start debugger
	&out("d");

	# Check the command status
	$ret = &out("e 08|000C");
	&out("x");
	
	# Exit
	&out("c");
	
	return substr($ret, 19, 2);
}

sub prepare()
{
	# Start debugger
	&out("d");
	
	# Put sector data into memory
	&out("e 08|0400");
	for($j = 0; $j < 9; $j+=1)
	{
		&out("00".sprintf("%02X", $j+8));
		&out("00".sprintf("%02X", $j));
	}
	&out("x");
	
	# Call the routine
	&out("c");
}

sub out()
{
	my $line = shift;
	my $in = shift;
	
#	print $line, "\n";
	$COM->write($line."\n");
	Time::HiRes::sleep(0.03);
	&in() unless $in;
}

sub in()
{
	my ($l1, $l2);
	while(!($l1 = $COM->input)) {}
	while(1)
	{
		Time::HiRes::sleep(0.03);
		$l2 .= $l1;
#		print $l1;
		$l1 = $COM->input;
		last unless $l1;
	}
	
	return $l2;
}
