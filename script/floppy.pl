#!/usr/bin/perl

use Win32::SerialPort;
use Time::HiRes;

$file = "disk1.bin";
$start = 0+$ARGV[0];

$COM = Win32::SerialPort->new("COM1");
$COM->baudrate(9600);
$COM->parity("N");
$COM->databits("8");
$COM->stopbits("1");
$COM->handshake("none");

open IN, $file;
binmode IN;
$sector = 0;
while(1)
{
	sysseek IN, 512*$sector, 0;
	sysread IN, $buffer, 512, 0;
	last if length($buffer) < 512;
	write_sector($sector, $buffer) if($sector >= $start);
	$sector++;
}

exit;

for($i = 0; $i < 1000; $i++)
{
	$sect = int(1024*rand());
	write_sector($sect, "Michau rulez!");
}
&in();

sub write_sector()
{
	my $nr = shift;
	my $data = shift;
	my $id;
	my $time;
	
	$time = time();
	print STDERR "Writing sector #$nr...\n";
	
	# Start debugger
	&out("d");
	
	# Lay &out(disk write command
	&out("e 08|0010");
	&out("0A20");
	&out(sprintf("%04X", $nr));
	&out("0100");
	&out("0804");
	&out("0000");
	&out("0000");
	&out("FF00");
	&out(sprintf("%04X", $nr));
	&out("x");
	
	# Put sector data into memory
	&out("e 08|0400");
	for($i = 0; $i < 512; $i+=2)
	{
		&out(sprintf("%02X", ord(substr($data, $i, 1))) . sprintf("%02X", ord(substr($data, $i+1, 1))));
	}
	&out("x");
	
	# Set PC to disk access routine
	&out("R pc 0000111E");
	
	# Call the routine
	&out("c");

	print STDERR "Write done in " . (time()-$time) . " seconds.\n";
	&out("?");
	
	# Repeat
	&out("d");
	&out("R pc 0000111E");
	&out("c");

	# Repeat
	&out("d");
	&out("R pc 0000111E");
	&out("c");
}

sub out()
{
	my $line = shift;
	my $in = shift;
	
#	print $line, "\n";
	$COM->write($line."\n");
	&in() unless $in;
}

sub in()
{
	my ($l1, $l2);
	while(!($l1 = $COM->input)) {}
	while(1)
	{
		Time::HiRes::sleep(0.01);
#		print $l1;
		$l1 = $COM->input;
		last unless $l1;
	}
}
