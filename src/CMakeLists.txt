########################################################
# CMake file for building SSbarProcessor
# @author Yuichi Okugawa, IJCLab
CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)
SET(CMAKE_OSX_ARCHITECTURES "x86_64")
########################################################

FILE(GLOB SOURCE_FILES
     "*.cc"
)

INCLUDE_DIRECTORIES(src
  PUBLIC
  ../include
)

ADD_LIBRARY(src
  SHARED
  ${SOURCE_FILES}
)

TARGET_INCLUDE_DIRECTORIES(src
  PUBLIC
  ../include
)

# target_link_libraries(ECALSIM ${ROOT_LIBRARIES})