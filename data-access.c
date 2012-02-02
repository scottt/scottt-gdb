#include <stdio.h>

struct bag {
	int a, b;
};

static void bag_poke(struct bag *p)
{
	p->a = 1;
}

static void bag_dump(struct bag *p)
{
	fprintf(stderr, "bag { a: %d, b: %d }\n", p->a, p->b);
}

int main()
{
	struct bag b = { 0 };
	bag_poke(&b);
	bag_dump(&b);
	return 0;
}
