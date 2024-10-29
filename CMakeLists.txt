project(BPACC_FUN C)

set(APP_SRC_FILES
  fsw/src/bpacc_fun_app.c
  fsw/src/bpacc_fun_cmds.c
  fsw/src/bpacc_fun_utils.c
)

if (CFE_EDS_ENABLED_BUILD)
  list(APPEND APP_SRC_FILES
    fsw/src/bpacc_fun_eds_dispatch.c
  )
else()
  list(APPEND APP_SRC_FILES
    fsw/src/bpacc_fun_dispatch.c
  )
endif()

# Create the app module
add_cfe_app(bpacc_fun ${APP_SRC_FILES})

target_include_directories(bpacc_fun PUBLIC fsw/inc)
# Include the public API from sample_lib to demonstrate how
# to call library-provided functions
add_cfe_app_dependency(bpacc_fun sample_lib)

# Add table
add_cfe_tables(bpacc_fun fsw/tables/bpacc_fun_tbl.c)

# If UT is enabled, then add the tests from the subdirectory
# Note that this is an app, and therefore does not provide
# stub functions, as other entities would not typically make
# direct function calls into this application.
if (ENABLE_UNIT_TESTS)
  add_subdirectory(unit-test)
endif (ENABLE_UNIT_TESTS)
