#!/usr/bin/env perl
use strict;
use warnings;

use Math::Prime::Util qw/-nobigint next_prime is_prime prime_iterator/;

my $count = shift || 20;

# Find Sophie Germain primes (numbers where p and 2p+1 are both prime).

# In this method, we add a filter in front of our iterator, to create a
# Sophie-Germain-prime iterator.  This isn't the fastest way, but it's still
# 20x faster than Math::NumSeq::SophieGermainPrimes at 300k.  If we add the
# two-line precalc shown below, we can get another 4x or so more.

sub get_sophie_germain_iterator {
  my $p = shift || 2;
  my $it = prime_iterator($p);
  return sub {
    do { $p = $it->() } while !is_prime(2*$p+1);
    $p;
  };
}
my $sgit = get_sophie_germain_iterator();
for (1..$count) {
  print $sgit->(), "\n";
}


# Method 2.  At 300k this is 70x faster than Math::NumSeq::SophieGermainPrimes.
#
# my $estimate = 100 + int( nth_prime_upper($count) * 1.6 * log($count) );
# prime_precalc(2 * $estimate);
# 
# my $prime = 2;
# for (1..$count) {
#   $prime = next_prime($prime) while (!is_prime(2*$prime+1));
#   print "$prime\n";
#   $prime = next_prime($prime);
# }

# Alternate method, 10-20% faster, would benefit from a tighter estimate.
#
# my $numfound = 0;
# forprimes {
#   if ($numfound < $count && is_prime(2*$_+1)) {
#     print "$_\n";
#     $numfound++;
#   }
# } $estimate;
# die "Estimate too low" unless $numfound >= $count;
