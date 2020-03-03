
#include <sys/__assert.h>

// __assert invokes '__ASSERT_PRINT' zephyr's 'sys/__assert.h'.
//
// __assert is invoked by 'assert' from the SEGGER runtime library's
// assert.h.
//
// 'assert' is invoked by many, one user is 'NRFX_ASSERT' from
// 'modules/hal/nordic/nrfx_glue.h'
void __assert(const char *__expression, const char *__filename, int __line)
{
	__ASSERT_PRINT(
		"ASSERTION FAIL [%s] @ %s:%d\n",
		__expression,
		__filename,
		__line
	);
}
