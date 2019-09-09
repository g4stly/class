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
struct R_Point {
	int x, y;			// instance variables
};

/*\
 * What I call the "Object Struct"
 * where everything connects
\*/
struct _Point {
	struct R_Point representation;	// representation
	const struct PointCls *cls;	// class definition
	struct Point interface;		// interface
};

// definitions of the methods + ctor and dtor
static int get_x(struct Point *_self)
{
	struct _Point *self = GET_OBJ(_self, struct R_Point);
	return self->representation.x;
}

static int get_y(struct Point *_self)
{
	struct R_Point *self = GET_OBJ(_self, struct R_Point);
	return self->y;
}

static void set_x(struct Point *_self, int x)
{
	struct R_Point *self = GET_OBJ(_self, struct R_Point);
	self->x = x;
}

static void set_y(struct Point *_self, int y)
{
	struct R_Point *self = GET_OBJ(_self, struct R_Point);
	self->y = y;
}

static void print(struct Point *_self)
{
	struct _Point *self = GET_OBJ(_self, struct R_Point);
	struct R_Point *r = &self->representation;
	fprintf(stdout, self->cls->prnt, r->x, r->y);
}

/*\
 * Where you build the object struct
\*/
static void *point_ctor(void *_self, va_list *ap)
{
	struct _Point *self = _self;

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

static void *point_dtor(void *_self)
{	// return original address passed to the ctor
	// do any other cleanup you might need to do
	return GET_OBJ(_self, struct R_Point);
}

// initialize and declare our class definition
static struct PointCls _Point = {
	{
		sizeof(struct _Point),
		point_ctor,
		point_dtor
	},
	"x: %i\ny: %i\n"
};
const void *Point = &_Point;
