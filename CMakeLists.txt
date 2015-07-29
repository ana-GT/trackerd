cmake_minimum_required( VERSION 2.8 )

find_package( PkgConfig )
pkg_check_modules( LIBUSB libusb-1.0 )
include_directories( ${LIBUSB_INCLUDE_DIRS} )

pkg_check_modules( GLIB glib-2.0 )
include_directories( ${GLIB_INCLUDE_DIRS} )

# Eigen
pkg_check_modules( EIGEN REQUIRED eigen3 )
include_directories( ${EIGEN_INCLUDE_DIRS} )

# Ach and sns needed
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}  ${CMAKE_SOURCE_DIR}/cmake/Modules )

# amino, ach and reflex
find_package( amino REQUIRED )
include_directories( ${AMINO_INCLUDE_DIRS} )
find_package( ach REQUIRED )
include_directories( ${ACH_INCLUDE_DIRS} )
find_package( sns REQUIRED )
include_directories( ${SNS_INCLUDE_DIRS} )

add_library( PiTracker TrackerUnit.cpp TrackerUnit.h PiTracker.cpp PiTracker.h )
target_link_libraries( PiTracker ${LIBUSB_LIBRARIES} ${GLIB_LIBRARIES} pthread )
set_target_properties( PiTracker PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib )

add_executable( trackerd trackerd.cpp trackerd.h tracker_msg.cpp tracker_msg.h )
target_link_libraries( trackerd PiTracker ${LIBUSB_LIBRARIES} ${GLIB_LIBRARIES} pthread ${ACH_LIBRARIES} ${SNS_LIBRARIES} )
set_target_properties( trackerd PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

add_executable( readTracker readTracker.cpp tracker_msg.cpp )
target_link_libraries( readTracker ${ACH_LIBRARIES} ${SNS_LIBRARIES} )
set_target_properties( readTracker PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )