#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <class.h>
#include "util.h"

void *new(const void *class, ...)
{
	const struct cls *c = class;
	if (!c) die("new(): null class descriptor!");

	void *obj = malloc(c->size);
	if (!obj) die("new(): malloc():");
	memset(obj, 0, c->size);

	if (c->ctor) {
		va_list ap;
		va_start(ap, class);
		obj = c->ctor(obj, &ap);
		va_end(ap);
	}

	// obj now points to the interface
	const struct cls ** class_def = obj - sizeof(void *);
	*class_def = class;

	return obj;
}

const struct cls *get_cls(void *obj)
{
	return *(const struct cls **)(obj - sizeof(void *));
}

void delete(void *obj)
{
	if (!obj) return;
	const struct cls *c = get_cls(obj);
	if (c && c->dtor) obj = c->dtor(obj);
	free(obj);
}
