# This is a CMake for verified-storage
cmake_minimum_required(VERSION 3.8.0)

project(verified-storage VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# message(STATUS "Name: ${PROJECT_NAME}")
# message(STATUS "Version: ${PROJECT_VERSION}")

######################
# Boost C++ library
######################
#
set(BOOST_ROOT "/usr/local/lib/boost-1.73.0")
set(BOOST_MIN_VERSION 1.73.0)
set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs
set(Boost_USE_RELEASE_LIBS ON) # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS 
    system
    log
    thread
    regex
)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Fatal error: Boost (Version >= ${BOOST_MIN_VERSION}) required.\n")
endif()

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions( "-DHAS_BOOST" )
    add_definitions( "-DBOOST_LOG_DYN_LINK")
endif()

set(BOOST_LIBRARIES
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_LOG_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
)

add_subdirectory(persistent)
add_subdirectory(utils)
add_subdirectory(rlp)
add_subdirectory(keccak)
add_subdirectory(storage)
add_subdirectory(main)

# set(SOURCE rlp.cpp)
# add_executable(vn-rlp ${SOURCE})

# target_link_libraries(vn-rlp PRIVATE utils rlp)
