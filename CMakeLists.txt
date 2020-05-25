cmake_minimum_required(VERSION 3.8.0)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(patricia-merkle-trie)

set(patricia-merkle-trie_VERSION_MAJOR 0)
set(patricia-merkle-trie_VERSION_MINOR 1)
set(patricia-merkle-trie_VERSION_PATCH 0)

include(CTest)
enable_testing()

add_library(pmt src/patricia-merkle-trie.cpp)

set(SOURCE src/patricia-merkle-trie.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Use the boost::spirit parser for converting strings to numbers
option(USE_BOOST_SPIRIT_PARSER 
    "use the boost::spirit::qi parsers for converting strings to tuple attributes" 
    ON
)

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
    program_options
    system
    coroutine
    iostreams
    log
    filesystem
    timer
    serialization
    thread
    regex
    chrono
    date_time
)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Fatal error: Boost (Version >= ${BOOST_MIN_VERSION}) required.\n")
endif()

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions( "-DHAS_BOOST" )
    add_definitions( "-DBOOST_LOG_DYN_LINK")
    if(USE_BOOST_SPIRIT_PARSER)
        add_definitions( "-DUSE_BOOST_SPIRIT_PARSER" )
    endif()
    add_executable(${PROJECT_NAME} ${SOURCE})
    target_link_libraries(${PROJECT_NAME} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_SYSTEM_LIBRARY})
endif()

set(BOOST_LIBRARIES
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_LOG_LIBRARY}
    ${Boost_COROUTINE_LIBRARY}
    ${Boost_IOSTREAMS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_CHRONO_LIBRARY}
    ${Boost_TIMER_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
	${DYLIB_LIBRARY}
)


set(UTILS_INCLUDE_DIR "${SOURCE_DIR}/utils")
# set_target_properties(pmt patricia-merkle-trie PROPERTIES LINKER_LANGUAGE CXX)

message(STATUS "${PROJECT_SOURCE_DIR}")

# add_subdirectory(src)
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/utils")
include_directories("${PROJECT_SOURCE_DIR}/keccak")
include_directories("${PROJECT_SOURCE_DIR}/rlp")
include_directories("${PROJECT_SOURCE_DIR}/includes")

