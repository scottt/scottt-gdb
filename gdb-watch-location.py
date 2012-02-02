import gdb

def _watch_location(expr, watch_point_class):
    l = gdb.parse_and_eval(expr).address
    wp_str = '*(%(type)s)(%(address)s)' % dict(type=l.type, address=l)
    gdb.Breakpoint(wp_str, gdb.BP_WATCHPOINT, watch_point_class)

class _WatchLocationCommand(gdb.Command):
    'Like "watch -l" in gdb 7.4+'
    def __init__(self):
        gdb.Command.__init__(self, 'watch-l', gdb.COMMAND_BREAKPOINTS, gdb.COMPLETE_SYMBOL)

    def invoke(self, arg, from_tty):
        _watch_location(arg, gdb.WP_WRITE)

class _RWatchLocationCommand(gdb.Command):
    'Like "rwatch -l" in gdb 7.4+'
    def __init__(self):
        gdb.Command.__init__(self, 'rwatch-l', gdb.COMMAND_BREAKPOINTS, gdb.COMPLETE_SYMBOL)

    def invoke(self, arg, from_tty):
        _watch_location(arg, gdb.WP_READ)

class _AWatchLocationCommand(gdb.Command):
    'Like "awatch -l" in gdb 7.4+'
    def __init__(self):
        gdb.Command.__init__(self, 'awatch-l', gdb.COMMAND_BREAKPOINTS, gdb.COMPLETE_SYMBOL)

    def invoke(self, arg, from_tty):
        _watch_location(arg, gdb.WP_ACCESS)

_WatchLocationCommand()
_RWatchLocationCommand()
_AWatchLocationCommand()
