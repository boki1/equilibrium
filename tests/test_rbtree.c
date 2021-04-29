#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "test_common.h"

int main(void)
{
	WarnIfNot(false);
	Ensure(true);
	return EXIT_SUCCESS;
}
