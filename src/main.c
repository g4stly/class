#include <stdio.h>
#include "class.h"
#include "point.h"

int main(int argc, char **argv)
{
	struct IPoint *p = new(Point, 2, 2);
	p->print(p);
	p->set_x(p, p->get_y(p) * 2);
	p->set_y(p, p->get_x(p) * 4);
	p->print(p);
	delete(p);
}
