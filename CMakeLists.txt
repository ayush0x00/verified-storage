cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 14)
project(patricia-merkle-trie VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(pmt patricia-merkle-trie.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Use LevelDB key-value store for implementing tables
option(USE_LEVELDB_TABLE "use LevelDB for implementing persistent tables" ON)

########################
# LevelDB database library 
########################
#
if (USE_LEVELDB_TABLE)
    message(STATUS "using LevelDB key-value store")
    add_definitions(-DUSE_LEVELDB_TABLE)
    set (LEVELDB_LIB "/usr/local/lib/libleveldb.a")
    include_directories("/usr/local/include/leveldb/include")
else()
    message(STATUS "don't use LevelDB key-value store")
    set (LEVELDB_LIB "")
endif()


# set(BOOST_ROOT "/usr/local/lib/boost-1.73.0")
set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs
set(Boost_USE_RELEASE_LIBS ON) # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(SOURCE patricia-merkle-trie.cpp)

find_package(Boost 1.73.0 COMPONENTS thread regex system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(${PROJECT_NAME} ${SOURCE})
    target_link_libraries(${PROJECT_NAME} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_SYSTEM_LIBRARY})
endif()

add_subdirectory(src)
