#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

char *program_name;

void hold_child(char **argv)
{
	int r;
	r = ptrace(PTRACE_TRACEME, 0, NULL, NULL);
	if (r == -1) {
		fprintf(stderr, "%s: PTRACE_TRACEME failed: %s\n", program_name, strerror(errno));
		exit(3);
	}
	r = execvp(argv[0], argv);
	fprintf(stderr, "%s: exec failed: %s\n", program_name, strerror(errno));
}

void print_usage_exit(void)
{
	fprintf(stderr, "usage: %s PROGRAM-TO-HOLD-FOR-DEBUGGING [ARGS ...]\n\n"
			"Afterwards, use:\n"
			"(gdb) attach PID\n"
			"(gdb) signal 0\n"
			"(gdb) signal 0\n"
			"to continue program execution after attaching to it in the debugger.\n",
			program_name);
	exit(2);
}

int main(int argc, char **argv)
{
	pid_t pid, t;
	int wstat, r;
	program_name = basename(argv[0]);

	if (argc < 2)
		print_usage_exit();

	if ((pid = fork()) > 0) {
		t = waitpid(pid, &wstat, 0);
		if (t == -1) {
			fprintf(stderr, "%s: waitpid failed: %s\n", program_name, strerror(errno));
			exit(3);
		}
		if (0) {
			fprintf(stderr, "%s: pid: %d, IFSTOPPED: %d, STOPSIG: %d\n",
					program_name, pid,
					WIFSTOPPED(wstat),
					WIFSTOPPED(wstat) ? WSTOPSIG(wstat) : -1);
		}
		if (!WIFSTOPPED(wstat) || WSTOPSIG(wstat) != SIGTRAP)
			exit(3);
		/* child process will continue as assume as ptrace tracer exits */
		r = kill(pid, SIGSTOP);
		if (r  == -1) {
			fprintf(stderr, "%s: kill failed: %s\n", program_name, strerror(errno));
			exit(3);
		}
		printf("%d\n", pid);
		exit(0);
	} else if (pid == 0) {
		hold_child(argv + 1);
	} else {
		fprintf(stderr, "%s: fork failed: %s\n", program_name, strerror(errno));
		exit(3);
	}
	return 0;
}
