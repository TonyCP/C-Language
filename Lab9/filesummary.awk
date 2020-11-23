#!/bin/gawk -f

BEGIN	{
	d = 0 #Directory Total
	f = 0 #Files Total	
	l = 0 #Links Total
	t = 0 #Overall Total
	s = 0
}

$1 ~ /^d[rwxts-]{9}/	{d += 1}
$1 ~ /^l[rwxts-]{9}/	{l += 1}
$1 ~ /^-[rwxts-]{9}/	{f += 1}
			 t = d + f + l
$5 ~ /^[0-9]/		{s += $5}


END	{print ""
	 print "Here is the summary of files under your home directory:"
	 print ""
	 printf("%-13s %-9s %-11s %-10s %-10s\n", "directories", "files", "links", "total", "storage(Bytes)")
	 print "============================================================"
	 printf("%-13d %-9d %-11d %-10d %-10d\n\n", d, f, l, t, s)
 }
