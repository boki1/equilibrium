#pragma once

// TODO: Remove stdlib dependancy
#if __STDC_HOSTED__
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#define errormsg(fmt, ...) \
	fprintf (stderr, "%s(%u): " fmt "\n", __FILE__, __LINE__, __VA_ARGS__)
#else
#define assert
#endif

#define Ensure(x) \
	assert(x)

#define EnsureEq(x, y) \
	assert((x) == (y));

#define EnsureNot(x) \
	assert(!(x));

#define WarnIf(x) \
	if ((x)) \
		errormsg("[warning]: '%s' is true", #x);

#define WarnIfNot(x) \
	WarnIf(!x);
