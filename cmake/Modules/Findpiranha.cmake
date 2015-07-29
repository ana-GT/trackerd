# *********************************************************
# Find piranha library
# Once done this will define:
# PIRANHA_FOUND - System has reflex installed
# PIRANHA_INCLUDE_DIRS - The reflex include directories
# PIRANHA_LIBRARIES - The libraries needed to use reflex
# *********************************************************

set( PIRANHA_FOLDER_PATH "/home/ana/Software/LWA4/piranha" )

# Find both paths where piranha header files live
find_path( piranha_frame_INCLUDE_DIR 
  NAMES pir-frame.h
  HINTS ${PIRANHA_FOLDER_PATH} )
find_path( piranha_main_INCLUDE_DIR
  NAMES piranha.h
  HINTS ${PIRANHA_FOLDER_PATH}/include )

# Put header paths together
set( piranha_INCLUDE_DIR ${piranha_frame_INCLUDE_DIR}
  ${piranha_main_INCLUDE_DIR} )

# Set library path
find_library( piranha_LIBRARY piranha
			HINTS /home/ana/Software/LWA4/piranha/.libs )

set( PIRANHA_LIBRARIES ${piranha_LIBRARY} )
set( PIRANHA_INCLUDE_DIRS ${piranha_INCLUDE_DIR} )

include( FindPackageHandleStandardArgs )

# Handle the QUIETLY and REQUIRED arguments and set PIRANHA_FOUND to TRUE
#if all listed variables are TRUE
find_package_handle_standard_args( piranha DEFAULT_MSG
  piranha_LIBRARY piranha_INCLUDE_DIR )
mark_as_advanced( piranha_INCLUDE_DIR piranha_LIBRARY )
