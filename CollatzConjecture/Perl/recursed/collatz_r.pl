#!/usr/bin/perl

# Collatz in Perl with Recursion
# Will Darragh

# MAX NUMBER
my $N = 10000;

sub collatz
{
	my $x = $_[0];

	if ( $x == 1 ) {
		return 0;
	} else {
		if ( $x%2 == 0 ) {
			$x = $x/2;
		} else {
			$x = 3*$x + 1;
		}
	return ( 1 + collatz($x) );
	}
}
sub small_index
{
        my $a = $_[0];
        my @lengths = @{$a};

        my $small = 0;
        my $smallest = $lengths[0];

        for my $i (0..$#lengths) {
                if ($lengths[$i] < $smallest) {
                        $smallest = $lengths[$i];
                        $small = $i;
                }
        }

        return $small;
}

my (@numbers, @lengths);
my ($length, $index, $smallest);

for ( 1..$N ) {
        $length = collatz($_);
        if (scalar(@numbers) < 10) {
                push @numbers, $_;
                push @lengths, $length;
        } else {
                $index = small_index(\@lengths);
                $smallest = $lengths[$index];

                if (($length > $smallest) || ($length == $smallest && $_ < $numbers[$index])) {
                        $numbers[$index] = $_;
                        $lengths[$index] = $length;
                }
        }

}

print "\tNumber\tLength\n";
for (0..$#numbers) {
        print "\t$numbers[$_]\t$lengths[$_]\n";
}

1;
