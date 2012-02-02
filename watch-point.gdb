file data-access
source gdb-watch-address.py
# break bag_poke doesn't work due to inlining, see:
# http://sourceware.org/gdb/current/onlinedocs/gdb/Inline-Functions.html
break data-access.c:9
commands
	rwatch -l p->b
	commands 2
		echo WATCH HIT\n
	end
end
run
