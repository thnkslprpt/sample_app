###########################################################
#
# BPACC_FUN_APP mission build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the BPACC_FUN_APP configuration
set(BPACC_FUN_APP_MISSION_CONFIG_FILE_LIST
  bpacc_fun_fcncodes.h
  bpacc_fun_interface_cfg.h
  bpacc_fun_mission_cfg.h
  bpacc_fun_perfids.h
  bpacc_fun_msg.h
  bpacc_fun_msgdefs.h
  bpacc_fun_msgstruct.h
  bpacc_fun_tbl.h
  bpacc_fun_tbldefs.h
  bpacc_fun_tblstruct.h
  bpacc_fun_topicids.h
)

if (CFE_EDS_ENABLED_BUILD)

  # In an EDS-based build, these files come generated from the EDS tool
  set(BPACC_FUN_APP_CFGFILE_SRC_bpacc_fun_interface_cfg "bpacc_fun_eds_designparameters.h")
  set(BPACC_FUN_APP_CFGFILE_SRC_bpacc_fun_tbldefs       "bpacc_fun_eds_typedefs.h")
  set(BPACC_FUN_APP_CFGFILE_SRC_bpacc_fun_tblstruct     "bpacc_fun_eds_typedefs.h")
  set(BPACC_FUN_APP_CFGFILE_SRC_bpacc_fun_msgdefs       "bpacc_fun_eds_typedefs.h")
  set(BPACC_FUN_APP_CFGFILE_SRC_bpacc_fun_msgstruct     "bpacc_fun_eds_typedefs.h")
  set(BPACC_FUN_APP_CFGFILE_SRC_bpacc_fun_fcncodes      "bpacc_fun_eds_cc.h")

endif(CFE_EDS_ENABLED_BUILD)

# Create wrappers around the all the config header files
# This makes them individually overridable by the missions, without modifying
# the distribution default copies
foreach(BPACC_FUN_APP_CFGFILE ${BPACC_FUN_APP_MISSION_CONFIG_FILE_LIST})
  get_filename_component(CFGKEY "${BPACC_FUN_APP_CFGFILE}" NAME_WE)
  if (DEFINED BPACC_FUN_APP_CFGFILE_SRC_${CFGKEY})
    set(DEFAULT_SOURCE GENERATED_FILE "${BPACC_FUN_APP_CFGFILE_SRC_${CFGKEY}}")
  else()
    set(DEFAULT_SOURCE FALLBACK_FILE "${CMAKE_CURRENT_LIST_DIR}/config/default_${BPACC_FUN_APP_CFGFILE}")
  endif()
  generate_config_includefile(
    FILE_NAME           "${BPACC_FUN_APP_CFGFILE}"
    ${DEFAULT_SOURCE}
  )
endforeach()
