#include <sys/errno_private.h>
#include <sys/libc-hooks.h>
#include <stdio.h>
#include <kernel.h>

// From SES runtime library.
// TODO: Put prototype in header file
int ctl_count_trailing_zeros_32(int);

int __ffssi2(int x)
{
	if(x == 0) {
		return 0;
	}
	return 1 + ctl_count_trailing_zeros_32(x);
}


// BEGIN libc_t_le_eabi.a overrides

// The symbols below (until 'END libc_t_le_eabi.a overrides') are
// replacing/overriding symbols that exist in libc_t_le_eabi.a, but
// that we for some reason want to use a different implementation for.

// In Zephyr the libc macro 'errno' must map to 'z_errno'. In SES,
// 'errno' either maps to '__errno' or '__aeabi_errno_addr' depending
// on if '__ARM_EABI__' is set or not.  We are currently defining
// __ARM_EABI__, so it maps to '__aeabi_errno_addr'. This symbol could
// be provided by libc_t_le_eabi.a, but if it was it would reference
// '__aeabi_read_tp', which does not exist in Zephyr.

volatile int *__aeabi_errno_addr(void)
{
	return z_errno();
}

// malloc, free, calloc reference __heap_{start,end}__, which is not
// defined, so we replace them with Zephyr variants intead.

void *malloc(size_t size)
{
	return k_malloc(size);
}

void free(void *ptr)
{
	k_free(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
	return calloc(nmemb, size);
}

// END libc_t_le_eabi.a overrides

// TODO: Implement the rest of the builtins.

// Not a builtin, but a libc function that is deliberately missing to
// allow users to direct where the printf output goes.
int __putchar(int c, __printf_tag_ptr unused)
{
	ARG_UNUSED(unused);
	
	return zephyr_fputc(c, stdout);
}

// mbedtls is configured to use 'exit', which we therefore provide a
// dummy implementation for.
void exit(int status)
{
	printk("exit\n");
	while (1) {
	}
}
