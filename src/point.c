#include <stdio.h>
#include <class.h>
#include "point.h"

/*\
 * This structure must extend cls
\*/
struct PointCls {
	struct cls super;	// extends cls
	const char *prnt;	// "static" field
};

/*\
 * The representation of your class
 * this struct holds instance variables and data
 * it must end with a pointer to the class definition
\*/
struct RPoint {
	int x, y;			// instance variables
	const struct PointCls *cls;	// class definition
};

/*\
 * What I call the "Object Struct"
 * where everything connects
\*/
struct Point {
	struct RPoint representation;
	struct IPoint interface;
};

// definitions of the methods + ctor and dtor
int get_x(struct IPoint *_self)
{
	struct Point *self = (void *)_self - sizeof(struct RPoint);
	return self->representation.x;
}

int get_y(struct IPoint *_self)
{
	struct RPoint *self = (void *)_self - sizeof(struct RPoint);
	return self->y;
}

void set_x(struct IPoint *_self, int x)
{
	struct RPoint *self = (void *)_self - sizeof(struct RPoint);
	self->x = x;
}

void set_y(struct IPoint *_self, int y)
{
	struct RPoint *self = (void *)_self - sizeof(struct RPoint);
	self->y = y;
}

void print(struct IPoint *_self)
{
	struct RPoint *self = (void *)_self - sizeof(struct RPoint);
	fprintf(stdout, self->cls->prnt, self->x, self->y);
}

/*\
 * Where you build the object struct
\*/
void *point_ctor(void *_self, va_list *ap)
{
	struct Point *self = _self;

	self->representation.x = va_arg(*ap, int);
	self->representation.y = va_arg(*ap, int);

	// the class is placed by the new function

	self->interface.print = print;
	self->interface.get_x = get_x;
	self->interface.set_x = set_x;
	self->interface.get_y = get_y;
	self->interface.set_y = set_y;
	
	// always return interface
	return &self->interface;
}

void *point_dtor(void *_self)
{	// return original address passed to the ctor
	// do any other cleanup you might need to do
	return _self - sizeof(struct RPoint);
}

// initialize and declare our class definition
static struct PointCls _Point = {
	{
		sizeof(struct Point),
		point_ctor,
		point_dtor
	},
	"x: %i\ny: %i\n"
};
const void *Point = &_Point;
