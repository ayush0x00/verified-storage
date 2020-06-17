# This is a CMake for verified-storage
cmake_minimum_required(VERSION 3.8.0)

# Include Hunter configurations
Include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.257.tar.gz"
    SHA1 "52203b35dfc2f975f4c22fc89f055476726e4288"
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(verified-storage VERSION 0.1.0)

# message(STATUS "Name: ${PROJECT_NAME}")
# message(STATUS "Version: ${PROJECT_VERSION}")

# Boost Header only library
hunter_add_package(Boost)
find_package(Boost CONFIG REQUIRED)

# Add project specific subdirectories
add_subdirectory(persistent)
add_subdirectory(utils)
add_subdirectory(rlp)
add_subdirectory(keccak)
add_subdirectory(storage)
add_subdirectory(main)

# set(SOURCE storage.cpp)
# add_executable(vn-storage ${SOURCE})

# target_link_libraries(vn-storage PRIVATE persistent utils rlp keccak storage)

