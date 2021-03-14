#!/usr/bin/perl
use strict;
use warnings;

# tableau
my @tab;

#lecture sur stdin 
while (<>)
{
    
    chomp; # supprime le retour à la ligne
    if ($_=~ /(\d\d-\d\d-\d\d-\d\d-\d\d)/)
    {
        push(@tab,$1);
    }
    elsif ($_=~ /(\+33-\d-\d\d-\d\d-\d\d-\d\d)/)
    {
        push(@tab,$1);
    }
    
}

print "numeros de telephone :\n", join ("\n",@tab), "\n";
