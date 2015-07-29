# *********************************************************
# Find OpenNI2 library
# Once done this will define
# OpenNI2_FOUND
# OpenNI2_INCLUDE_DIRS
# OpenNI2_LIBRARIES
# *********************************************************

find_path( OpenNI2_INCLUDE_DIR OpenNI.h HINTS $ENV{OPENNI2_INCLUDE} )
find_library( OpenNI2_LIBRARY
  NAMES OpenNI2 OniFile PS1080 
  HINTS $ENV{OPENNI2_REDIST}
  $ENV{OPENNI2_REDIST}/OpenNI2/Drivers
  PATH_SUFFIXES lib)

set( OpenNI2_INCLUDE_DIRS ${OpenNI2_INCLUDE_DIR} )
set( OpenNI2_LIBS ${OpenNI2_LIBRARY} )
message( "Openni2 libraries: ${OpenNI2_LIBRARY}" )

include( FindPackageHandleStandardArgs )

# Handle the QUIETLY AND REQUIRED arguments and set OpenNI2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args( OpenNI2 DEFAULT_MSG
  OpenNI2_INCLUDE_DIR OpenNI2_LIBRARY )
mark_as_advanced( OpenNI2_INCLUDE_DIR OpenNI2_LIBRARY )
