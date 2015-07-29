# *********************************************************
# Find reflex library
# Once done this will define:
# REFLEX_FOUND - System has reflex installed
# REFLEX_INCLUDE_DIRS - The reflex include directories
# REFLEX_LIBRARIES - The libraries needed to use reflex
# *********************************************************

find_path( reflex_INCLUDE_DIR reflex.h 
            HINTS /home/ana/Software/LWA4/reflex/include )
find_library( reflex_LIBRARY reflex
	    HINTS /home/ana/Software/LWA4/reflex/.libs )

set( REFLEX_LIBRARIES ${reflex_LIBRARY} )
set( REFLEX_INCLUDE_DIRS ${reflex_INCLUDE_DIR} )

include( FindPackageHandleStandardArgs )

# Handle the QUIETLY and REQUIRED arguments and set AMINO_FOUND to TRUE
#if all listed variables are TRUE
find_package_handle_standard_args( reflex DEFAULT_MSG
  reflex_LIBRARY reflex_INCLUDE_DIR )
mark_as_advanced( reflex_INCLUDE_DIR reflex_LIBRARY )
