# SPDX-License-Identifier: Apache-2.0

# Configuration for host installed clang
#

set(NOSTDINC "")

# Note that NOSYSDEF_CFLAG may be an empty string, and
# set_ifndef() does not work with empty string.
if(NOT DEFINED NOSYSDEF_CFLAG)
  set(NOSYSDEF_CFLAG -undef)
endif()

if(DEFINED TOOLCHAIN_HOME)
  set(find_program_clang_args PATH ${TOOLCHAIN_HOME} NO_DEFAULT_PATH)
endif()

# TODO: Fix
find_program(CMAKE_C_COMPILER   $ENV{HOME}/developmentstudio-2019.1/sw/ARMCompiler6.13/bin/armclang   ${find_program_clang_args})
find_program(CMAKE_CXX_COMPILER clang++ ${find_program_clang_args})

if(NOT "${ARCH}" STREQUAL "posix")
  include(${ZEPHYR_BASE}/cmake/gcc-m-cpu.cmake)

  unset(armclang_target_flag)
  if("${ARCH}" STREQUAL "arm")
    # TODO: Only when 'armclang'
    set(armclang_target_flag --target=arm-arm-none-eabi)

    list(APPEND TOOLCHAIN_C_FLAGS
      -fshort-enums
      ${armclang_target_flag}
      )
    list(APPEND TOOLCHAIN_LD_FLAGS
      -fshort-enums
      )

    include(${ZEPHYR_BASE}/cmake/compiler/gcc/target_arm.cmake)
  endif()

  foreach(file_name include/stddef.h include-fixed/limits.h)
    execute_process(
      COMMAND ${CMAKE_C_COMPILER} --print-file-name=${file_name}
      OUTPUT_VARIABLE _OUTPUT
      )
    get_filename_component(_OUTPUT "${_OUTPUT}" DIRECTORY)
    string(REGEX REPLACE "\n" "" _OUTPUT ${_OUTPUT})

    list(APPEND NOSTDINC ${_OUTPUT})
  endforeach()

  foreach(isystem_include_dir ${NOSTDINC})
    list(APPEND isystem_include_flags -isystem ${isystem_include_dir})
  endforeach()

  # This libgcc code is partially duplicated in compiler/*/target.cmake
  execute_process(
    COMMAND ${CMAKE_C_COMPILER} ${TOOLCHAIN_C_FLAGS} --print-libgcc-file-name
    OUTPUT_VARIABLE LIBGCC_FILE_NAME
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

#  assert_exists(LIBGCC_FILE_NAME)

  get_filename_component(LIBGCC_DIR ${LIBGCC_FILE_NAME} DIRECTORY)

#  assert_exists(LIBGCC_DIR)

  list(APPEND LIB_INCLUDE_DIR "-L\"${LIBGCC_DIR}\"")
  list(APPEND TOOLCHAIN_LIBS $<TARGET_PROPERTY:zephyr_property_target,c_runtime_library>)

  if(CONFIG_ARMV6_M_ARMV8_M_BASELINE)
    set(arch_attr p)
  else()
    # It is not clear if 'w' is correct, it could be p, or r instead.
    set(arch_attr w)
  endif()

  set_property(TARGET
    zephyr_property_target
    PROPERTY
    c_runtime_library
#    "gcc"
    "$ENV{ZEPHYR_TOOLCHAIN_ARM_COMPILER_6_DIR}/lib/armlib/c_${arch_attr}.l" # TODO: Fix
    )

  set(CMAKE_REQUIRED_FLAGS -nostartfiles -nostdlib ${isystem_include_flags})

  # Ignore that __main is undefined.
  if(ARMCLANG)
    list(APPEND CMAKE_REQUIRED_FLAGS
      ${armclang_target_flag}
      -Xlinker --partial
      )
  else()
    list(APPEND CMAKE_REQUIRED_FLAGS
      -Wl,--unresolved-symbols=ignore-in-object-files
      )
  endif(ARMCLANG)

  string(REPLACE ";" " " CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS}")

endif()

# Load toolchain_cc-family macros

macro(toolchain_cc_nostdinc)
  if(NOT "${ARCH}" STREQUAL "posix")
    zephyr_compile_options( -nostdinc)
  endif()
endmacro()

# Clang and GCC are almost feature+flag compatible, so reuse freestanding gcc
include(${ZEPHYR_BASE}/cmake/compiler/gcc/target_security_canaries.cmake)
include(${ZEPHYR_BASE}/cmake/compiler/gcc/target_optimizations.cmake)
include(${ZEPHYR_BASE}/cmake/compiler/gcc/target_cpp.cmake)
include(${ZEPHYR_BASE}/cmake/compiler/gcc/target_asm.cmake)
include(${ZEPHYR_BASE}/cmake/compiler/gcc/target_baremetal.cmake)
include(${ZEPHYR_BASE}/cmake/compiler/${COMPILER}/target_warnings.cmake)
include(${ZEPHYR_BASE}/cmake/compiler/gcc/target_imacros.cmake)
include(${ZEPHYR_BASE}/cmake/compiler/gcc/target_base.cmake)
include(${ZEPHYR_BASE}/cmake/compiler/${COMPILER}/target_coverage.cmake)
include(${ZEPHYR_BASE}/cmake/compiler/${COMPILER}/target_sanitizers.cmake)

macro(toolchain_cc_security_fortify)
  # No op, clang doesn't understand fortify at all
endmacro()

macro(toolchain_cc_no_freestanding_options)
  # No op, this is used by the native_posix, clang has problems
  # compiling the native_posix with -fno-freestanding.
endmacro()
