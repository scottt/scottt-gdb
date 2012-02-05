#include <stdio.h>
#include "embed-breakpoint.h"

int main()
{
	printf("Hello,\n");
	EMBED_BREAKPOINT;
	printf("world!\n");
	EMBED_BREAKPOINT;
	return 0;
}
