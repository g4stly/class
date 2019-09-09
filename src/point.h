#ifndef point_h_
#define point_h_

// expose this header and link point.c
// and any third party can use new() and delete()
// with the Point class and use it without any knowledge
// of the internals.

struct Point {
	void (*print)(struct Point *self);
	int (*get_x)(struct Point *self);
	void (*set_x)(struct Point *self, int x);
	int (*get_y)(struct Point *self);
	void (*set_y)(struct Point *self, int y);
};

extern const void *Point;

#endif
