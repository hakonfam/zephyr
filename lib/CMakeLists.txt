# SPDX-License-Identifier: Apache-2.0

if(NOT CONFIG_EXTERNAL_LIBC)
add_subdirectory(libc)
add_subdirectory(posix)
endif()
add_subdirectory_ifdef(CONFIG_CMSIS_RTOS_V1        cmsis_rtos_v1)
add_subdirectory_ifdef(CONFIG_CMSIS_RTOS_V2        cmsis_rtos_v2)
add_subdirectory(gui)
add_subdirectory(os)
add_subdirectory_ifdef(CONFIG_UPDATEHUB            updatehub)

set_property(TARGET
  zephyr_property_target
  PROPERTY
  c_runtime_library
  ""
  )

set(compiler_rt_dir llvm-project/compiler-rt)
set(builtins_dir ${compiler_rt_dir}/lib/builtins)

zephyr_library()

function(filter_builtin_sources output_var exclude_or_include excluded_list)
  if(exclude_or_include STREQUAL "EXCLUDE")
    set(filter_action GREATER)
    set(filter_value -1)
  elseif(exclude_or_include STREQUAL "INCLUDE")
    set(filter_action LESS)
    set(filter_value 0)
  else()
    message(FATAL_ERROR "filter_builtin_sources called without EXCLUDE|INCLUDE")
  endif()

  set(intermediate ${ARGN})
  foreach (_file ${intermediate})
    get_filename_component(_name_we ${_file} NAME_WE)
    list(FIND ${excluded_list} ${_name_we} _found)
    if(_found ${filter_action} ${filter_value})
      list(REMOVE_ITEM intermediate ${_file})
    elseif(${_file} MATCHES ".*/.*\\.S" OR ${_file} MATCHES ".*/.*\\.c")
      get_filename_component(_name ${_file} NAME)
      string(REPLACE ".S" ".c" _cname "${_name}")
      list(REMOVE_ITEM intermediate ${_cname})
    endif ()
  endforeach ()
  set(${output_var} ${intermediate} PARENT_SCOPE)
endfunction()

set(GENERIC_SOURCES
  absvdi2.c
  absvsi2.c
  absvti2.c
  adddf3.c
  addsf3.c
  addtf3.c
  addvdi3.c
  addvsi3.c
  addvti3.c
  apple_versioning.c
  ashldi3.c
  ashlti3.c
  ashrdi3.c
  ashrti3.c
  bswapdi2.c
  bswapsi2.c
  clzdi2.c
  clzsi2.c
  clzti2.c
  cmpdi2.c
  cmpti2.c
  comparedf2.c
  comparesf2.c
  ctzdi2.c
  ctzsi2.c
  ctzti2.c
  divdc3.c
  divdf3.c
  divdi3.c
  divmoddi4.c
  divmodsi4.c
  divsc3.c
  divsf3.c
  divsi3.c
  divtc3.c
  divti3.c
  divtf3.c
  extendsfdf2.c
  extendhfsf2.c
  ffsdi2.c
  ffssi2.c
  ffsti2.c
  fixdfdi.c
  fixdfsi.c
  fixdfti.c
  fixsfdi.c
  fixsfsi.c
  fixsfti.c
  fixunsdfdi.c
  fixunsdfsi.c
  fixunsdfti.c
  fixunssfdi.c
  fixunssfsi.c
  fixunssfti.c
  floatdidf.c
  floatdisf.c
  floatsidf.c
  floatsisf.c
  floattidf.c
  floattisf.c
  floatundidf.c
  floatundisf.c
  floatunsidf.c
  floatunsisf.c
  floatuntidf.c
  floatuntisf.c
  fp_mode.c
  int_util.c
  lshrdi3.c
  lshrti3.c
  moddi3.c
  modsi3.c
  modti3.c
  muldc3.c
  muldf3.c
  muldi3.c
  mulodi4.c
  mulosi4.c
  muloti4.c
  mulsc3.c
  mulsf3.c
  multi3.c
  multf3.c
  mulvdi3.c
  mulvsi3.c
  mulvti3.c
  negdf2.c
  negdi2.c
  negsf2.c
  negti2.c
  negvdi2.c
  negvsi2.c
  negvti2.c
  os_version_check.c
  paritydi2.c
  paritysi2.c
  parityti2.c
  popcountdi2.c
  popcountsi2.c
  popcountti2.c
  powidf2.c
  powisf2.c
  powitf2.c
  subdf3.c
  subsf3.c
  subvdi3.c
  subvsi3.c
  subvti3.c
  subtf3.c
  trampoline_setup.c
  truncdfhf2.c
  truncdfsf2.c
  truncsfhf2.c
  ucmpdi2.c
  ucmpti2.c
  udivdi3.c
  udivmoddi4.c
  udivmodsi4.c
  udivmodti4.c
  udivsi3.c
  udivti3.c
  umoddi3.c
  umodsi3.c
  umodti3.c
  )

set(arm_SOURCES
  arm/fp_mode.c
  arm/bswapdi2.S
  arm/bswapsi2.S
  arm/clzdi2.S
  arm/clzsi2.S
  arm/comparesf2.S
  arm/divmodsi4.S
  arm/divsi3.S
  arm/modsi3.S
  arm/sync_fetch_and_add_4.S
  arm/sync_fetch_and_add_8.S
  arm/sync_fetch_and_and_4.S
  arm/sync_fetch_and_and_8.S
  arm/sync_fetch_and_max_4.S
  arm/sync_fetch_and_max_8.S
  arm/sync_fetch_and_min_4.S
  arm/sync_fetch_and_min_8.S
  arm/sync_fetch_and_nand_4.S
  arm/sync_fetch_and_nand_8.S
  arm/sync_fetch_and_or_4.S
  arm/sync_fetch_and_or_8.S
  arm/sync_fetch_and_sub_4.S
  arm/sync_fetch_and_sub_8.S
  arm/sync_fetch_and_umax_4.S
  arm/sync_fetch_and_umax_8.S
  arm/sync_fetch_and_umin_4.S
  arm/sync_fetch_and_umin_8.S
  arm/sync_fetch_and_xor_4.S
  arm/sync_fetch_and_xor_8.S
  arm/udivmodsi4.S
  arm/udivsi3.S
  arm/umodsi3.S
  )

set(arm_EABI_SOURCES
  arm/aeabi_cdcmp.S
  arm/aeabi_cdcmpeq_check_nan.c
  arm/aeabi_cfcmp.S
  arm/aeabi_cfcmpeq_check_nan.c
  arm/aeabi_dcmp.S
  arm/aeabi_div0.c
  arm/aeabi_drsub.c
  arm/aeabi_fcmp.S
  arm/aeabi_frsub.c
  arm/aeabi_idivmod.S
  arm/aeabi_ldivmod.S
  arm/aeabi_memcmp.S
  arm/aeabi_memcpy.S
  arm/aeabi_memmove.S
  arm/aeabi_memset.S
  arm/aeabi_uidivmod.S
  arm/aeabi_uldivmod.S
  )

set(thumb1_SOURCES
  arm/divsi3.S
  arm/udivsi3.S
  arm/comparesf2.S
  arm/addsf3.S
)

filter_builtin_sources(arm_SOURCES    EXCLUDE arm_SOURCES    "${arm_SOURCES};${GENERIC_SOURCES}")

filter_builtin_sources(thumb1_SOURCES EXCLUDE thumb1_SOURCES "${thumb1_SOURCES};${GENERIC_SOURCES}")

if(CONFIG_CPU_CORTEX_M0 OR CONFIG_CPU_CORTEX_M0PLUS)
  set(srcs
    ${thumb1_SOURCES}
    ${arm_EABI_SOURCES}
    )
else()
  set(srcs
    ${arm_SOURCES}
    ${arm_EABI_SOURCES}
    )
endif()

foreach(src ${srcs})
  zephyr_library_sources(
    ${builtins_dir}/${src}
    )
endforeach()
