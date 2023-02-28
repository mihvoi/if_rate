if_rate : a network bandwidth monitoring tool with very low overhead

                       "Linux interface rate monitor"

How it looks like:
<pre>
	Averages for the last 1003 msec
	----------------------------------------------------------------------
	|| IF         ||Input                    ||Output                   ||
	----------------------------------------------------------------------
	||  eth0      ||    458 kbps|    804 pk/s||  97055 kbps|   8023 pk/s||
	||    lo      ||      0 kbps|      0 pk/s||      0 kbps|      0 pk/s||
	----------------------------------------------------------------------
</pre>

<pre>
Usage:
  Compile: "make"
  Run: ./if_rate 3
  Install: sudo make install

  If you trust my build, you can just use: ./static_build_ia32/if_rate


About:
  This is a "Hello world!" clone. Please read copyright notes from "Kernigam
& Ritchie" papers! Just kidding ...
  
  This is a simple program who reads from /proc/net/dev and writes real-time statistics 
  about the trafic on interfaces. 
  
  You can use it free (and without waranties)
  I hope you will find it usefull and you will use it only for moral purposes :)

  Known bugs: - some interface drivers have bugs in the update of the counter,
		not my fault...
	      - some drivers have time counters updated at more than 1 second
		interval; in order to have exact averages you must set an interval 
		much bigger than this interval (example: "./if_rate 10")


  Updates:
  2.0.0 
	- the rate is more accured, now I use gettimeofday() for exact time
	measuring.
	- more space for gigabit counters
	- accept argument - number of seconds between counters is settable

  2.1.0
	- use counters on 64bits for Gigabit Ethernet cards
	- more space for Gigabit Ethernet speeds

  2.1.2
	- packaging fixes

  2.1.3 
	- reformat output
	- first commit on github.com

  This was initially shared by me many years ago (2001) on http://freecode.com/projects/if_rate

  Mihai Voicu
  mihvoi@gmail.com
  
  Some philosophy: https://philosophymeans.blogspot.com/

</pre>
