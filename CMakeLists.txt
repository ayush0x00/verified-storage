cmake_minimum_required(VERSION 3.8.0)
include(CMakePackageConfigHelpers)
include(CMakeDependentOption)

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(varifiedstorage)
set(varifiedstorage_VERSION_MAJOR 0)
set(varifiedstorage_VERSION_MINOR 1)
set(varifiedstorage_VERSION_PATCH 0)
set(varifiedstorage_VERSION ${varifiedstorage_VERSION_MAJOR}.${varifiedstorage_VERSION_MINOR},${varifiedstorage_VERSION_PATCH})
set(PACKAGE_VERSION ${varifiedstorage_VERSION})
set(VERSION "${varifiedstorage_VERSION}")

# set(SOURCE src/patricia-merkle-trie.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(CTest)
enable_testing()

#Options
option(VERIFIEDSTORAGE_STATIC "Build static library" ON)
option(VERIFIEDSTORAGE_SHARED "Build shared libraru" ON)
option(VERIFIEDSTORAGE_LOG "Build with logs" ON)
# Use the boost::spirit parser for converting strings to numbers
option(USE_BOOST_SPIRIT_PARSER 
    "use the boost::spirit::qi parsers for converting strings to tuple attributes" 
    ON
)
# Use LevelDB key-value store for implementing tables
option(USE_LEVELDB_TABLE "use LevelDB for implementing persistent tables" ON)

find_package(Doxygen)
option(VERIFIEDSTORAGE_DOCUMENTATION "Create and install the HTML based API documentation (requires doxygen)" ${DOXYGEN_FOUND})

#Dependecies
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

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
    # add_executable(${PROJECT_NAME} ${SOURCE})
    # target_link_libraries(${PROJECT_NAME} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_SYSTEM_LIBRARY})
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

#Build Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-return-type -Wall -Wextra -Wnon-virtual-dtor -pedantic-errors -fvisibility=hidden")

link_directories(
    ./
    utils/
    keccak/
    rlp/
    rlp/inc/
    ${CMAK_CURRENT_BINARY_DIR}/include/
)

#  Install dirs
include (GNUInstallDirs)
set (prefix ${CMAKE_INSTALL_PREFIX})
set (exec_prefix "\${prefix}")
set (libdir "\${exec_prefix}/${CMAKE_INSTALL_LIBDIR}")
set (includedir "\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}")
set (bindir "${CMAKE_INSTALL_FULL_BINDIR}")
set (sysconfdir "${CMAKE_INSTALL_FULL_SYSCONFDIR}")
set (top_srcdir "${CMAKE_CURRENT_SOURCE_DIR}")

#sources
list(APPEND varifiedstorage_HEADERS
    src/core/alias.hpp
    src/core/constants.hpp
    src/core/nodetype.hpp
    src/utils/generalised.hpp
    src/utils/hex.hpp
    src/utils/nibbles.hpp
    src/core/batchdbop.hpp
    src/core/db.hpp
    src/core/node.hpp
    src/core/branch.hpp
    src/core/extension.hpp
    src/core/leaf.hpp
    src/core/db.hpp
    src/core/nodeutils.hpp
    src/core/path.hpp
    src/core/vtrie.hpp    
)

list(APPEND varifiedstorage_SOURCES
    src/utils/hex.cpp
    src/utils/nibbles.cpp
    src/core/batchdbop.cpp
    src/core/db.cpp
    src/core/node.cpp
    src/core/branch.cpp
    src/core/extension.cpp
    src/core/leaf.cpp
    src/core/db.cpp
    src/core/nodeutils.cpp
    src/core/path.cpp
    src/core/vtrie.cpp
)

# Targets
if(VERIFIEDSTORAGE_STATIC)
    add_library(varifiedstorage-static STATIC 
        ${varifiedstorage_SOURCES}
        ${varifiedstorage_HEADERS}
    )
    set_target_properties(varifiedstorage-static PROPERTIES OUTPUT_NAME "verifiedstorage")
    target_include_directories(varifiedstorage-static SYSTEM PRIVATE utils)
    target_include_directories(varifiedstorage-static SYSTEM PRIVATE keccak)
    target_include_directories(varifiedstorage-static SYSTEM PRIVATE rlp)
    install(TARGETS varifiedstorage-static DESTINATION ${CMAKE_INSTALL_LIBDIR} EXPORT varifiedstorage)
endif()
