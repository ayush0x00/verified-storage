set(SOURCE main.cpp)
add_executable(verified-network ${SOURCE})

target_link_libraries(verified-network PRIVATE constants utils rlp keccak storage)
