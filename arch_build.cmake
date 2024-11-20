###########################################################
#
# BPACC_FUN platform build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the BPACC_FUN configuration
set(BPACC_FUN_PLATFORM_CONFIG_FILE_LIST
  bpacc_fun_internal_cfg.h
  bpacc_fun_platform_cfg.h
  bpacc_fun_perfids.h
  bpacc_fun_msgids.h
)

# Create wrappers around the all the config header files
# This makes them individually overridable by the missions, without modifying
# the distribution default copies
foreach(BPACC_FUN_CFGFILE ${BPACC_FUN_PLATFORM_CONFIG_FILE_LIST})
  get_filename_component(CFGKEY "${BPACC_FUN_CFGFILE}" NAME_WE)
  if (DEFINED BPACC_FUN_CFGFILE_SRC_${CFGKEY})
    set(DEFAULT_SOURCE GENERATED_FILE "${BPACC_FUN_CFGFILE_SRC_${CFGKEY}}")
  else()
    set(DEFAULT_SOURCE FALLBACK_FILE "${CMAKE_CURRENT_LIST_DIR}/config/default_${BPACC_FUN_CFGFILE}")
  endif()
  generate_config_includefile(
    FILE_NAME           "${BPACC_FUN_CFGFILE}"
    ${DEFAULT_SOURCE}
  )
endforeach()
