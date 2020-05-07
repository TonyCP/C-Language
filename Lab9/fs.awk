#!/bin/gawk -f

BEGIN	{
	d = 0	# count for number of directory
		# define more variables here.
	}

$1 ~ /^d[rwxts-]{9}/	{d += 1}	# directory
					# add more here.

END	{print ""
	 print "Here is the summary of files under your home directory:"
	 print ""
	 print "directories   files     links      total       storage(Bytes)"
	 print "============================================================="
	 printf "%-13d %-9d %-11d %-10d %-10d\n\n", d # more coming
	} 
