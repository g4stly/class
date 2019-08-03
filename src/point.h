#ifndef point_h_
#define point_h_

struct IPoint {
	void (*print)(struct IPoint *self);
	int (*get_x)(struct IPoint *self);
	void (*set_x)(struct IPoint *self, int x);
	int (*get_y)(struct IPoint *self);
	void (*set_y)(struct IPoint *self, int y);
};

extern const void *Point;

#endif
