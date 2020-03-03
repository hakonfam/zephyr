# The C low-level runtime library provides routines that are
# automatically invoked when C code of a certain form is written, for
# instance 64bit division on a 32bit architecture.
#
# It is very compiler-specific and nearly always provided by the
# compiler itself, e.g. through libgcc.a on gcc. But it is possible
# and sometimes necessary, e.g. for licensing reasons, to link in a
# replacement for the runtime library.
#
# This library is not the same thing as the C library. The C library
# is a portable and documented part of the C standard, whereas the
# runtime library is not.

# These build scripts allow users to link in an alternative runtime
# library to the one that is provided by the compiler.

# SES.
#
# This was tested and reverse-engineered from
# 'arm_segger_embedded_studio_v420a_linux_x64_nordic'
#
# lib<library_type>_<configuration>.a
#
# library_type = {cxxabi,c,cpp,m,vfscanf,vfprintf,debugio,debugio_mempoll,debugio_bkpt}
#
# The ones we are interested in for now are 'm' and 'c'. It appears
# that all library types support all configurations.
#
# configuration:
#
# Some configurations support all other configurations, and others are
# only conditionally present. For instance certain FPU's are only
# present on certain architectures.
#
# The configurations can be combined with all other configurations:
#
# library_type, arch, small, swc, ienum.
#
# <arch>_<float>_t_le_eabi[_small][_swc][_ienum].a
#
# arch:
# v6m
# v7em
# v7m
# v8mbl
# v8mml
#
# float:
# {fpv4,fpv5}[_sp][_d16][_hard]
#
# hard denotes the ABI and is only present when the fpu is
# specified. It could be combined with any float configuration.
#

if(CONFIG_C_RUNTIME_SEGGER)

if(SEGGER_SES_DIR)
  # CONF_FILE has either been specified on the cmake CLI or is already
  # in the CMakeCache.txt. This has precedence over the environment
  # variable CONF_FILE and the default prj.conf
elseif(DEFINED ENV{SEGGER_SES_DIR})
  set(SEGGER_SES_DIR $ENV{SEGGER_SES_DIR})

endif(SEGGER_SES_DIR)

set(SEGGER_SES_DIR ${SEGGER_SES_DIR} CACHE STRING "")

set(SEGGER_SES_LIB_DIR
  ${SEGGER_SES_DIR}/lib
  )

if(CONFIG_CPU_CORTEX_M0 OR CONFIG_CPU_CORTEX_M0PLUS)
  set(SEGGER_ARCH v6m)
elseif(CONFIG_CPU_CORTEX_M3)
  set(SEGGER_ARCH v7m)
elseif(CONFIG_CPU_CORTEX_M4 OR CONFIG_CPU_CORTEX_M7)
  set(SEGGER_ARCH v7em)
elseif(CONFIG_CPU_CORTEX_M23 OR CONFIG_CPU_CORTEX_M33)
  set(SEGGER_ARCH v8mml)
else()
  # There also exists v8mbl, but the difference between v8mbl and
  # v8mml is not known yet.

  # NB:
  # set(ARCH_FOR_cortex-m23       armv8-m.base    )
  # set(ARCH_FOR_cortex-m33       armv8-m.main+dsp)
  # set(ARCH_FOR_cortex-m33+nodsp armv8-m.main    )

  message(FATAL_ERROR "CONFIG_C_RUNTIME_SEGGER was enabled.
But it is not known which library should be used for this architecture.")
endif()

set(configuration
  ${SEGGER_ARCH}
  )

if(CONFIG_FLOAT)
  string(APPEND configuration
    _${FPU_FOR_${GCC_M_CPU}}
    )

  if(NOT CONFIG_CPU_HAS_FPU_DOUBLE_PRECISION)
    string(APPEND configuration
      _sp
      )
  endif(NOT CONFIG_CPU_HAS_FPU_DOUBLE_PRECISION)

  string(APPEND configuration
    _d16
    )

  if(CONFIG_FP_HARDABI)
    string(APPEND configuration
      _hard
      )
  endif()
endif(CONFIG_FLOAT)

# __aeabi_ddiv does floating point division and is provided by libm.a
# in SES, whereas it is provided by libgcc.a in 'gnuarmemb'. Therefore
# we must always link in 'libm' when using SES.

set(SEGGER_RUNTIME_LIBRARIES
  ${SEGGER_SES_LIB_DIR}/libc_${configuration}_t_le_eabi.a
  ${SEGGER_SES_LIB_DIR}/libm_${configuration}_t_le_eabi.a
  )

set_property(TARGET
  zephyr_property_target
  PROPERTY
  c_runtime_library
  "${SEGGER_RUNTIME_LIBRARIES}"
  )

# TODO: Will this cause aliasing issues with e.g. stdint.h ? assert.h ?
#zephyr_include_directories(${SEGGER_SES_DIR}/include/gcc)

# TODO: Should we use a zephyr-specific libc include dir, a
# libc-specific libc include dir, or the toolchain include dir?
#zephyr_include_directories(${SEGGER_SES_DIR}/include)

# When we use SEGGER for the C library we need for instance size_t to
# be defined by SEGGER. Usually it will come from minimal lib or
# newlib through the file stdlib.h.  To instruct the SEGGER runtime
# library to define size_t, we must set the define __CROSSWORKS_ARM
# and __ARM_EABI__.
# TODO: Could/Should something else set these?
zephyr_compile_definitions(
  __ARM_EABI__
  __SES_ARM
  BUILTIN_OFFSETOF # TODO: Put this somewhere more scalable
  )

# TODO: Is it possible to ignore the warning given by SES's offsetof ?

# Akin to size_t, ssize_t is provided by
# /home/sebo/ncs/zephyr/lib/libc/minimal/include/sys/types.h, but it's
# def. uses __SIZE_TYPE__.

# We need EBUSY to be defined. It could be defined by

# /home/sebo/ncs/zephyr/lib/libc/minimal/include/errno.h
# #define EBUSY 16	/* Mount device busy */

# /home/sebo/Downloads/gcc-arm-none-eabi-8-2019-q3-update/arm-none-eabi/include/sys/errno.h
# 48:#define	EBUSY 16	/* Device or resource busy */
#
# But SES's errno.h implementation does not define it unfortunately,
# nor does it appear to be defined anywhere else in SES.
#
# EBUSY is a POSIX.1-2001 error code. Maybe SES is not posix-compliant.

if(NOT CONFIG_ASSERT)
  # Do this to remove all __assert symbols.
  # TODO: Investigate if this has unwanted side-effects.
  zephyr_compile_definitions(NDEBUG)
endif()

zephyr_include_directories(
  .
  ${SEGGER_SES_DIR}/include
  )

# __vfprintf.c provides '__vfprintf', which is used by
# "libc_<arch>_t_le_eabi.a: in function `snprintf'"
zephyr_library_named(ses_vfprintf)
zephyr_library_sources(
  ${SEGGER_SES_DIR}/source/__vfprintf.c
   )

zephyr_library_compile_definitions(
  UNIX # This selects the printf implementation that we integrate with
  )

zephyr_library()
zephyr_library_sources(
  gcc_builtins.c
  )

zephyr_library_sources_ifdef(
  CONFIG_ASSERT
  __assert.c
  )

zephyr_library_sources_ifdef(
  CONFIG_ASSERT
  __assert.c
  )

zephyr_library_sources_ifdef(
  CONFIG_PRINTK
  prf.c
  stdout_console.c
  # TODO: Don't copy these from 'minimal libc'
  )

# cmse functions are usually provided by the runtime library, but in
# the SEGGER case they are provided as source code.
zephyr_library_sources_ifdef(
  CONFIG_CPU_CORTEX_M_HAS_CMSE
  ${SEGGER_SES_DIR}/source/cmse.c
  )

# NB: SEGGER_SES_DIR/user_libc.c should not be included because it
# references '__tbss_start__' which we do not have in Zephyr.

# __assert is missing. How does the user end up referencing this?
# Could we re-direct it to something we do support?
# How does minimal and newlib provide __assert?
# What does SES support wrt. assert?
# Should we implement our own __assert?
# Should we consider __assert non-portable and ban it's usage?
#
# minimal libc re-directs 'assert' to __ASSERT_NO_MSG'. Let's do the
# same. TODO: Should this be in a re-usable libc-agnostic Zephyr
# module?
#
# Hmm, seems SES's assert.h is taking priority over our own, and this
# assert.h requires a __assert to be defined ... Okay, let's try
# defining __assert then.

# We require that when using the SEGGER runtime library, you also use
# the SEGGER C library, not an unreasonable request I would
# say. Testing has shown that the SEGGER runtime library integrates
# with 'gnuarmemb', but it does not integrate with newlib's libc.

# TODO: Fix 'offsetof' warning

# Once upon a time the libc function 'read' was implemented in
# libc-hooks. Presumably because 'read' was not present in libc, but
# we needed it because it was present in "minimal libc", which was
# supported first.
#
# Eventually, one found out that this 'read' function should be
# renamed from 'read' to 'z_zephyr_read_stdin', and I'm sure this was
# the correct decision. Now, the problem is, that it no longer has
# anything to do with libc and therefore does not belong in
# libc-hooks.
#
# zephyr/subsys/shell/shell_fprintf.c:shell_fprintf_fmt references
# either z_prf or z_vprintk depending on whether NEWLIB_LIBC is
# enabled or not.
#
# z_vprintk is provided by zephyr/lib/os/printk.c and implements the
# printf formatting algorithm. It is used when NEWLIB_LIBC is enabled.
#
# z_prf also implements the printf formatting algorithm, it is
# provided by minimal libc.
#
# It's not clear which, if any, should be used. We choose to use z_prf
# because we have used other parts of minimal libc earlier.
#
# 'putchar' (actually __putchar), is referenced by
# libc_t_le_eabi.a:printf.
#
# SES requires the user to implement putchar. Perhaps we could
# implement it with the console? Or with 'zephyr_fputc'?
#
# How do other systems do this?

endif(CONFIG_C_RUNTIME_SEGGER)
