* gdb-watch-address.py: adds a "watch-l" that works like "watch -l" in GDB 7.4+
* embed-breakpoint.h, gdb-with-breakpoints.py: insert breakpoints in source like DebugBreak() but store the breakpoint addresses in a separate "embed-breakpoints" section that can be read by a program.
* hold: start a child process but "hold" it so that you can attach to it in a debugger first
