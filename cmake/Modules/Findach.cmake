# *********************************************************
# Find ach library
# Once done this will define:
# ACH_FOUND - System has amino installed
# ACH_INCLUDE_DIRS - The amino include directories
# ACH_LIBRARIES - The libraries needed to use amino
# *********************************************************

find_path( ach_INCLUDE_DIR ach.h PATHS /home/ana/local/include )
find_library( ach_LIBRARY ach PATHS /home/ana/local/lib )

set( ACH_LIBRARIES ${ach_LIBRARY} )
set( ACH_INCLUDE_DIRS ${ach_INCLUDE_DIR} )

include( FindPackageHandleStandardArgs )

# Handle the QUIETLY and REQUIRED arguments and set AMINO_FOUND to TRUE
#if all listed variables are TRUE
find_package_handle_standard_args( ach DEFAULT_MSG
  ach_LIBRARY ach_INCLUDE_DIR )
mark_as_advanced( ach_INCLUDE_DIR ach_LIBRARY )
