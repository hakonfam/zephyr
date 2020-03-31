# SPDX-License-Identifier: Apache-2.0

# Configures binary toos as llvm binary tool set

if(DEFINED TOOLCHAIN_HOME)
  set(find_program_clang_args PATH ${TOOLCHAIN_HOME} NO_DEFAULT_PATH)
  set(find_program_binutils_args PATH ${TOOLCHAIN_HOME})
endif()

find_program(CMAKE_AR      llvm-ar      ${find_program_clang_args}   )
find_program(CMAKE_NM      /home/sebo/Downloads/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-nm      ${find_program_clang_args}   )
find_program(CMAKE_OBJDUMP /home/sebo/Downloads/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-objdump ${find_program_clang_args}   )
find_program(CMAKE_RANLIB  llvm-ranlib  ${find_program_clang_args}   )
find_program(CMAKE_OBJCOPY /home/sebo/Downloads/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-objcopy ${find_program_binutils_args})
# TODO: Fix
find_program(CMAKE_READELF readelf      ${find_program_binutils_args})

# Use the gnu binutil abstraction macros
include(${ZEPHYR_BASE}/cmake/bintools/gnu/target_memusage.cmake)
include(${ZEPHYR_BASE}/cmake/bintools/gnu/target_objcopy.cmake)
include(${ZEPHYR_BASE}/cmake/bintools/gnu/target_objdump.cmake)
include(${ZEPHYR_BASE}/cmake/bintools/gnu/target_readelf.cmake)
include(${ZEPHYR_BASE}/cmake/bintools/gnu/target_strip.cmake)
