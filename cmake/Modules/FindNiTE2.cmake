# *********************************************************
# Find NiTE2 library
# Once done this will define
# NiTE2_FOUND
# NiTE2_INCLUDE_DIRS
# NiTE2_LIBRARIES
# *********************************************************

find_path( NiTE2_INCLUDE_DIR NiTE.h HINTS $ENV{NITE2_INCLUDE} )
find_library( NiTE2_LIBRARY NAMES NiTE2 PATHS $ENV{NITE2_REDIST64} )

set( NiTE2_INCLUDE_DIRS ${NiTE2_INCLUDE_DIR} )
set( NiTE2_LIBS ${NiTE2_LIBRARY} )

include( FindPackageHandleStandardArgs )

# Handle the QUIETLY AND REQUIRED arguments and set NiTE2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args( NiTE2 DEFAULT_MSG
  NiTE2_INCLUDE_DIR NiTE2_LIBRARY )
mark_as_advanced( NiTE2_INCLUDE_DIR NiTE2_LIBRARY )