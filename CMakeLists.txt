cmake_minimum_required(VERSION 2.8)
project( seekCV )


SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11" )

find_package( OpenCV 3.0 REQUIRED )
find_package( PkgConfig )
pkg_check_modules( LIBUSB_1 REQUIRED libusb-1.0 )
pkg_check_modules( LIBSEEK REQUIRED seek )

message(STATUS " - Includes: ${OpenCV_INCLUDE_DIRS}")
message(STATUS " - Libraries: ${OpenCV_LIBS}")

message(STATUS " - Includes: ${LIBUSB_1_INCLUDE_DIRS}")
message(STATUS " - Libraries: ${LIBUSB_1_LIBRARIES}")

message(STATUS " - Includes: ${LIBSEEK_INCLUDE_DIRS}")
message(STATUS " - Libraries: ${LIBSEEK_LIBRARIES}")

include_directories( ${OpenCV_INCLUDE_DIRS} ${LIBUSB_1_INCLUDE_DIR} ${LIBSEEK_INCLUDE_DIR} )
add_executable( seekCV seekCV.cpp )
target_link_libraries( seekCV ${OpenCV_LIBS} ${LIBUSB_1_LIBRARIES} ${LIBSEEK_LIBRARIES})

