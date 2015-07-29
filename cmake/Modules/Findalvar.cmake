# *********************************************************
# Find alvar library
# Once done this will define:
# ALVAR_FOUND - System has amino installed
# ALVAR_INCLUDE_DIRS - The amino include directories
# ALVAR_LIBRARIES - The libraries needed to use amino
# *********************************************************

set( ALVAR_ROOT_DIR /home/ana/local )

find_path( alvar_INCLUDE_DIR Alvar.h PATHS ${ALVAR_ROOT_DIR}/include/alvar ) # NO_DEFAULT_PATH
find_library( alvar_LIBRARY alvar200 PATHS ${ALVAR_ROOT_DIR}/lib ) # NO_DEFAULT_PATH

set( ALVAR_LIBRARIES ${alvar_LIBRARY} )
set( ALVAR_INCLUDE_DIRS ${alvar_INCLUDE_DIR} )

include( FindPackageHandleStandardArgs )

# Handle the QUIETLY and REQUIRED arguments and set AMINO_FOUND to TRUE
#if all listed variables are TRUE
find_package_handle_standard_args( alvar DEFAULT_MSG
  alvar_LIBRARY alvar_INCLUDE_DIR )
mark_as_advanced( alvar_INCLUDE_DIR alvar_LIBRARY )
