#!/bin/gawk -f

# This awk script is to process the /etc/passwd file
BEGIN	{FS = ":"
	 uid = 0
	 gid = 0
	 print ""
	 print "Here are the results:\n"
	 print "user_name password uid   gid   full_name        home            shell"
	 print "=============================================================================="
	}
	{printf"%-12s %-5s %-5d %-5d %-16s %-16s %-16s\n", \
		substr($1,0,10), substr($2,0,10), $3, $4, \
		substr($5,0,16), substr($6,0,16), substr($7,0,16)

# add more actions here.
	if($3 > uid)
		uid = $3

	if($4 > gid)
		gid = $4
	}
END	{print "=============================================================================="
	 print "Next available uid: " uid + 1
	 print "Next available gid: " (gid + 1)
	}
